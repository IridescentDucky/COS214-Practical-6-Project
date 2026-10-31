#include "GenericApi.h"
#include "httplib.h"

#include "BonusScoreDecorator.h"
#include "BonusTimeDecorator.h"
#include "Caretaker.h"
#include "Composite.h"
#include "ConcreteStrategyA.h"
#include "ConcreteStrategyB.h"
#include "ConcreteStrategyC.h"
#include "TIVIDY.h"
#include "WorkItem.h"

#include <cstdio>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace
{

struct ItemExtras
{
    int deadline;
    int timeSpent;
    int snapshots;
};

struct ItemTemplate
{
    std::string name;
    int deadline;
};

struct Group
{
    std::string name;
    std::vector<int> members;
    std::unique_ptr<Composite<int> > composite;
};

struct GenericSession
{
    TIVIDY<int> tividy;
    std::map<int, ItemExtras> extras;
    std::vector<std::pair<int, int> > dependencies;
    std::map<int, std::unique_ptr<Caretaker<int> > > history;
    std::vector<ItemTemplate> templates;
    std::string strategy = "Average";
    std::vector<Group> groups;
};

struct ScoringRule
{
    std::string label;
    std::function<Strategy<int>*()> make;
};

class RequestError : public std::runtime_error
{
public:
    explicit RequestError(const std::string& message) : std::runtime_error(message)
    {
    }
};

class CoutCapture
{
public:
    CoutCapture() : original(std::cout.rdbuf(buffer.rdbuf()))
    {
    }

    ~CoutCapture()
    {
        std::cout.rdbuf(original);
    }

    std::vector<std::string> lines() const
    {
        std::vector<std::string> result;
        std::istringstream input(buffer.str());
        std::string line;
        while (std::getline(input, line))
        {
            std::string::size_type start = line.find_first_not_of(" \t");
            if (start != std::string::npos)
            {
                result.push_back(line.substr(start));
            }
        }
        return result;
    }

private:
    std::ostringstream buffer;
    std::streambuf* original;
};

typedef std::function<void(GenericSession&, AbstractWorkItem<int>*, const httplib::Request&)> ItemAction;

std::mutex sessionMutex;
std::unique_ptr<GenericSession> session(new GenericSession());

std::string escapeJson(const std::string& text)
{
    std::string out;
    for (std::string::size_type i = 0; i < text.size(); ++i)
    {
        unsigned char c = static_cast<unsigned char>(text[i]);
        if (c == '"' || c == '\\')
        {
            out += '\\';
            out += static_cast<char>(c);
        }
        else if (c == '\n')
        {
            out += "\\n";
        }
        else if (c < 0x20)
        {
            char code[8];
            std::snprintf(code, sizeof(code), "\\u%04x", c);
            out += code;
        }
        else
        {
            out += static_cast<char>(c);
        }
    }
    return out;
}

std::string quote(const std::string& text)
{
    return "\"" + escapeJson(text) + "\"";
}

std::string snapshotJson(const GenericSession& current, const std::string& action,
                         const std::vector<std::string>& log, const std::string& error)
{
    std::ostringstream json;
    json << "{\"items\":[";
    std::unique_ptr<Iterator<int> > it(current.tividy.createIterator());
    bool first = true;
    while (it->hasNext())
    {
        AbstractWorkItem<int>* item = it->next();
        ItemExtras extra = current.extras.at(item->getId());
        json << (first ? "" : ",")
             << "{\"id\":" << item->getId()
             << ",\"name\":" << quote(item->getName())
             << ",\"state\":" << quote(item->getStateName())
             << ",\"data\":" << quote(item->get())
             << ",\"deadline\":" << extra.deadline
             << ",\"timeSpent\":" << extra.timeSpent
             << ",\"snapshots\":" << extra.snapshots
             << ",\"overdue\":" << item->getOverdue()
             << ",\"tasks\":[";
        for (int i = 0; i < item->getTaskCount(); ++i)
        {
            const TaskRecord& task = item->getTask(i);
            json << (i > 0 ? "," : "") << "{\"name\":" << quote(task.name) << ",\"score\":" << task.score
                 << ",\"max\":" << task.maxScore << "}";
        }
        json << "]}";
        first = false;
    }
    json << "],\"dependencies\":[";
    for (std::vector<std::pair<int, int> >::size_type i = 0; i < current.dependencies.size(); ++i)
    {
        json << (i > 0 ? "," : "") << "[" << current.dependencies[i].first << ","
             << current.dependencies[i].second << "]";
    }
    json << "],\"strategy\":" << quote(current.strategy) << ",\"templates\":[";
    for (std::vector<ItemTemplate>::size_type i = 0; i < current.templates.size(); ++i)
    {
        json << (i > 0 ? "," : "") << "{\"name\":" << quote(current.templates[i].name)
             << ",\"deadline\":" << current.templates[i].deadline << "}";
    }
    json << "],\"groups\":[";
    for (std::vector<Group>::size_type i = 0; i < current.groups.size(); ++i)
    {
        const Group& group = current.groups[i];
        json << (i > 0 ? "," : "") << "{\"name\":" << quote(group.name) << ",\"members\":[";
        for (std::vector<int>::size_type m = 0; m < group.members.size(); ++m)
        {
            json << (m > 0 ? "," : "") << group.members[m];
        }
        json << "],\"score\":" << group.composite->getScore() << ",\"time\":" << group.composite->getTime() << "}";
    }
    json << "],\"action\":" << quote(action) << ",\"log\":[";
    for (std::vector<std::string>::size_type i = 0; i < log.size(); ++i)
    {
        json << (i > 0 ? "," : "") << quote(log[i]);
    }
    json << "],\"error\":" << quote(error) << "}";
    return json.str();
}

std::string nameParam(const httplib::Request& req, const std::string& key, const std::string& what)
{
    std::string name = req.get_param_value(key);
    std::string::size_type start = name.find_first_not_of(" \t");
    std::string::size_type end = name.find_last_not_of(" \t");
    if (start == std::string::npos)
    {
        throw RequestError("Give the " + what + " a name");
    }
    std::string trimmed = name.substr(start, end - start + 1);
    if (trimmed.size() > 40)
    {
        throw RequestError("Name must be 40 characters or fewer");
    }
    return trimmed;
}

void registerItem(GenericSession& s, int id, int deadline)
{
    ItemExtras extra = { deadline, 0, 0 };
    s.extras[id] = extra;
    s.history[id].reset(new Caretaker<int>());
}

int intParam(const httplib::Request& req, const std::string& key, int low, int high)
{
    if (!req.has_param(key))
    {
        throw RequestError("Missing " + key);
    }
    int value = 0;
    try
    {
        value = std::stoi(req.get_param_value(key));
    }
    catch (const std::exception&)
    {
        throw RequestError(key + " must be a whole number");
    }
    if (value < low || value > high)
    {
        throw RequestError(key + " must be between " + std::to_string(low) + " and " + std::to_string(high));
    }
    return value;
}

AbstractWorkItem<int>* findItem(GenericSession& current, int id)
{
    std::unique_ptr<Iterator<int> > it(current.tividy.createIterator());
    while (it->hasNext())
    {
        AbstractWorkItem<int>* item = it->next();
        if (item->getId() == id)
        {
            return item;
        }
    }
    throw RequestError("No work item with id " + std::to_string(id));
}

void runAction(httplib::Response& res, const std::string& action,
               const std::function<void(GenericSession&)>& body)
{
    std::lock_guard<std::mutex> lock(sessionMutex);
    std::vector<std::string> log;
    std::string error;
    try
    {
        CoutCapture capture;
        try
        {
            body(*session);
        }
        catch (...)
        {
            log = capture.lines();
            throw;
        }
        log = capture.lines();
    }
    catch (const RequestError& e)
    {
        error = e.what();
        res.status = 400;
    }
    res.set_content(snapshotJson(*session, action, log, error), "application/json");
}

std::map<std::string, ItemAction> buildItemActions()
{
    std::map<std::string, ItemAction> actions;

    actions["advance"] = [](GenericSession& s, AbstractWorkItem<int>* item, const httplib::Request&)
    {
        s.tividy.advanceWork(item->getId());
    };
    actions["submit"] = [](GenericSession& s, AbstractWorkItem<int>* item, const httplib::Request& req)
    {
        s.tividy.submitWork(item->getId(), req.get_param_value("data"));
    };
    actions["pause"] = [](GenericSession& s, AbstractWorkItem<int>* item, const httplib::Request&)
    {
        s.tividy.pauseWork(item->getId());
    };
    actions["resume"] = [](GenericSession& s, AbstractWorkItem<int>* item, const httplib::Request&)
    {
        s.tividy.resumeWork(item->getId());
    };

    actions["fail"] = [](GenericSession&, AbstractWorkItem<int>* item, const httplib::Request&)
    {
        item->failed();
    };
    actions["failedDelivery"] = [](GenericSession&, AbstractWorkItem<int>* item, const httplib::Request&)
    {
        item->failedDelivery();
    };
    actions["exception"] = [](GenericSession&, AbstractWorkItem<int>* item, const httplib::Request&)
    {
        item->exception();
    };
    actions["retry"] = [](GenericSession&, AbstractWorkItem<int>* item, const httplib::Request&)
    {
        item->retry();
    };
    actions["validate"] = [](GenericSession&, AbstractWorkItem<int>* item, const httplib::Request&)
    {
        item->validate();
    };
    actions["time"] = [](GenericSession& s, AbstractWorkItem<int>* item, const httplib::Request& req)
    {
        int units = intParam(req, "units", 1, 1000);
        s.tividy.logTime(item->getId(), units);
        ItemExtras& extra = s.extras[item->getId()];
        extra.timeSpent += units;
        std::cout << "[UI] Logged " << units << " time unit(s) on " << item->getName() << " ("
                  << extra.timeSpent << "/" << extra.deadline << ")" << std::endl;
    };

    actions["task"] = [](GenericSession& s, AbstractWorkItem<int>* item, const httplib::Request& req)
    {
        std::string name = nameParam(req, "name", "task");
        int maxScore = intParam(req, "max", 1, 1000);
        int score = intParam(req, "score", 0, maxScore);
        s.tividy.addTask(item->getId(), name, score, maxScore);
    };
    actions["template"] = [](GenericSession& s, AbstractWorkItem<int>* item, const httplib::Request&)
    {
        if (s.tividy.saveAsTemplate(item->getId()) < 0)
        {
            throw RequestError("Could not save the template");
        }
        ItemTemplate saved = { item->getName(), s.extras[item->getId()].deadline };
        s.templates.push_back(saved);
    };

    actions["snapshot"] = [](GenericSession& s, AbstractWorkItem<int>* item, const httplib::Request&)
    {
        s.history[item->getId()]->addMemento(item->createMemento());
        s.extras[item->getId()].snapshots++;
    };
    actions["restore"] = [](GenericSession& s, AbstractWorkItem<int>* item, const httplib::Request& req)
    {
        int saved = s.extras[item->getId()].snapshots;
        if (saved == 0)
        {
            throw RequestError("Save a snapshot first");
        }
        int index = intParam(req, "index", 0, saved - 1);
        item->setMemento(s.history[item->getId()]->getMemento(index));
    };

    actions["decorate"] = [](GenericSession&, AbstractWorkItem<int>* item, const httplib::Request& req)
    {
        std::vector<std::unique_ptr<Component<int> > > wrappers;
        Component<int>* current = item;
        if (req.get_param_value("score") == "1")
        {
            wrappers.push_back(std::unique_ptr<Component<int> >(new BonusScoreDecorator<int>(current, 10, 2)));
            current = wrappers.back().get();
        }
        if (req.get_param_value("time") == "1")
        {
            wrappers.push_back(std::unique_ptr<Component<int> >(new BonusTimeDecorator<int>(current, 3)));
            current = wrappers.back().get();
        }
        current->display();
        std::cout << "[Decorator] Score: " << current->getScore() << ", time: " << current->getTime() << std::endl;
    };

    return actions;
}

}

void registerGenericApi(httplib::Server& server)
{
    static const std::map<std::string, ItemAction> itemActions = buildItemActions();

    server.Get("/api/generic/state", [](const httplib::Request&, httplib::Response& res)
    {
        std::lock_guard<std::mutex> lock(sessionMutex);
        res.set_content(snapshotJson(*session, "", std::vector<std::string>(), ""), "application/json");
    });

    server.Post("/api/generic/reset", [](const httplib::Request&, httplib::Response& res)
    {
        {
            std::lock_guard<std::mutex> lock(sessionMutex);
            session.reset(new GenericSession());
        }
        runAction(res, "Reset workspace", [](GenericSession&)
        {
            std::cout << "[UI] Started a fresh TIVIDY session" << std::endl;
        });
    });

    server.Post("/api/generic/items", [](const httplib::Request& req, httplib::Response& res)
    {
        runAction(res, "Create work item", [&](GenericSession& s)
        {
            std::string name = nameParam(req, "name", "work item");
            int deadline = intParam(req, "deadline", 1, 1000);
            registerItem(s, s.tividy.createWorkItem(name, deadline), deadline);
        });
    });

    server.Post(R"(/api/generic/items/(\d+)/(\w+))", [](const httplib::Request& req, httplib::Response& res)
    {
        std::string name = req.matches[2];
        std::map<std::string, ItemAction>::const_iterator action = itemActions.find(name);
        if (action == itemActions.end())
        {
            res.status = 404;
            res.set_content("{\"error\":\"Unknown action\"}", "application/json");
            return;
        }
        int id = std::stoi(req.matches[1]);
        runAction(res, name, [&](GenericSession& s)
        {
            action->second(s, findItem(s, id), req);
        });
    });

    server.Post("/api/generic/dependencies", [](const httplib::Request& req, httplib::Response& res)
    {
        runAction(res, "Add dependency", [&](GenericSession& s)
        {
            int from = intParam(req, "from", 1, 1000000);
            int to = intParam(req, "to", 1, 1000000);
            if (s.tividy.addDependency(from, to))
            {
                s.dependencies.push_back(std::make_pair(from, to));
                AbstractWorkItem<int>* first = findItem(s, from);
                AbstractWorkItem<int>* then = findItem(s, to);
                std::cout << "[UI] " << then->getName() << " now waits for " << first->getName() << std::endl;
                if (first->getStateName() == "Completed" || first->getStateName() == "Archived")
                {
                    std::cout << "[UI] Note: " << first->getName() << " has already completed, so the mediator "
                              << "will not deliver " << then->getName() << " automatically" << std::endl;
                }
                if (then->getStateName() != "Created")
                {
                    std::cout << "[UI] Note: " << then->getName() << " has already left Created, so the mediator "
                              << "will leave it alone" << std::endl;
                }
            }
            else
            {
                throw RequestError("Dependency rejected: same item, unknown item or already linked");
            }
        });
    });

    server.Post("/api/generic/strategy", [](const httplib::Request& req, httplib::Response& res)
    {
        static const std::map<std::string, ScoringRule> rules = {
            { "average", { "Average", []() -> Strategy<int>* { return new ConcreteStrategyA<int>(); } } },
            { "highest", { "Highest", []() -> Strategy<int>* { return new ConcreteStrategyB<int>(); } } },
            { "lowest", { "Lowest", []() -> Strategy<int>* { return new ConcreteStrategyC<int>(); } } }
        };
        runAction(res, "Change scoring rule", [&](GenericSession& s)
        {
            std::map<std::string, ScoringRule>::const_iterator rule = rules.find(req.get_param_value("rule"));
            if (rule == rules.end())
            {
                throw RequestError("Unknown scoring rule");
            }
            s.tividy.setStrategy(rule->second.make());
            s.strategy = rule->second.label;
            std::cout << "[UI] Completed work is now scored by its " << s.strategy << " task score" << std::endl;
        });
    });

    server.Post(R"(/api/generic/templates/(\d+))", [](const httplib::Request& req, httplib::Response& res)
    {
        int index = std::stoi(req.matches[1]);
        runAction(res, "Create from template", [&](GenericSession& s)
        {
            if (index >= static_cast<int>(s.templates.size()))
            {
                throw RequestError("No template " + std::to_string(index));
            }
            int id = s.tividy.createFromTemplate(index);
            if (id < 0)
            {
                throw RequestError("Could not create from that template");
            }
            registerItem(s, id, s.templates[index].deadline);
        });
    });

    server.Post("/api/generic/groups", [](const httplib::Request& req, httplib::Response& res)
    {
        runAction(res, "Create group", [&](GenericSession& s)
        {
            std::string name = nameParam(req, "name", "group");
            for (std::vector<Group>::const_iterator it = s.groups.begin(); it != s.groups.end(); ++it)
            {
                if (it->name == name)
                {
                    throw RequestError("A group with that name already exists");
                }
            }
            Group group;
            group.name = name;
            group.composite.reset(new Composite<int>(name));
            s.groups.push_back(std::move(group));
            std::cout << "[Composite] Created group " << name << std::endl;
        });
    });

    server.Post(R"(/api/generic/groups/(\d+)/add)", [](const httplib::Request& req, httplib::Response& res)
    {
        int index = std::stoi(req.matches[1]);
        runAction(res, "Add to group", [&](GenericSession& s)
        {
            if (index >= static_cast<int>(s.groups.size()))
            {
                throw RequestError("No group " + std::to_string(index));
            }
            Group& group = s.groups[index];
            int id = intParam(req, "item", 1, 1000000);
            AbstractWorkItem<int>* item = findItem(s, id);
            for (std::vector<int>::const_iterator it = group.members.begin(); it != group.members.end(); ++it)
            {
                if (*it == id)
                {
                    throw RequestError(item->getName() + " is already in " + group.name);
                }
            }
            group.composite->add(item);
            group.members.push_back(id);
            std::cout << "[Composite] " << group.name << " now groups " << group.members.size() << " item(s):" << std::endl;
            group.composite->display();
        });
    });
}
