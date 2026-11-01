#include "WorkflowMediator.h"
#include "WorkItem.h"
#include "WorkItemIterator.h"
#include "ConcreteHandlerA.h"
#include "ConcreteStrategyA.h"
#include "Adapter.h"

#include <iostream>

template <typename T>
WorkflowMediator<T>::WorkflowMediator()
    : strategy(new ConcreteStrategyA<T>()), externalSystem(new Adaptee()), external(new Adapter(externalSystem))
{
    levels.push_back(std::make_pair(std::string("Team lead"), static_cast<T>(3)));
    levels.push_back(std::make_pair(std::string("Manager"), static_cast<T>(7)));
    levels.push_back(std::make_pair(std::string("Department head"), static_cast<T>(12)));
    levels.push_back(std::make_pair(std::string("Director"), static_cast<T>(18)));
    levels.push_back(std::make_pair(std::string("Executive"), static_cast<T>(25)));
}

template <typename T>
WorkflowMediator<T>::~WorkflowMediator()
{
    for (TaskEscalationManager<T>* escalation : escalations)
    {
        delete escalation;
    }
    for (AbstractWorkItem<T>* item : workItems)
    {
        delete item;
    }
    delete strategy;
    delete external;
    delete externalSystem;
}

template <typename T>
void WorkflowMediator<T>::addWorkItem(AbstractWorkItem<T>* item)
{
    if (item != nullptr && getWorkItem(item->getId()) == nullptr)
    {
        workItems.push_back(item);

        TaskEscalationManager<T>* chain = createChain();
        item->attach(chain);
        escalations.push_back(chain);
    }
}

template <typename T>
TaskEscalationManager<T>* WorkflowMediator<T>::createChain() const
{
    TaskEscalationManager<T>* first = nullptr;
    TaskEscalationManager<T>* last = nullptr;
    for (typename std::vector<std::pair<std::string, T> >::size_type i = 0; i < levels.size(); ++i)
    {
        TaskEscalationManager<T>* handler = new ConcreteHandlerA<T>(levels[i].first, levels[i].second);
        if (last == nullptr)
        {
            first = handler;
        }
        else
        {
            last->setSuccessor(handler);
        }
        last = handler;
    }
    return first;
}

template <typename T>
bool WorkflowMediator<T>::setEscalationLevels(const std::vector<std::pair<std::string, T> >& levels)
{
    if (levels.empty() || levels.size() > 5)
    {
        return false;
    }
    for (typename std::vector<std::pair<std::string, T> >::size_type i = 0; i < levels.size(); ++i)
    {
        if (levels[i].first.empty() || (i > 0 && !(levels[i - 1].second < levels[i].second)))
        {
            return false;
        }
    }

    for (TaskEscalationManager<T>* escalation : escalations)
    {
        delete escalation;
    }
    escalations.clear();
    this->levels = levels;

    for (AbstractWorkItem<T>* item : workItems)
    {
        TaskEscalationManager<T>* chain = createChain();
        item->attach(chain);
        escalations.push_back(chain);
    }
    return true;
}

template <typename T>
const std::vector<std::pair<std::string, T> >& WorkflowMediator<T>::getEscalationLevels() const
{
    return levels;
}

template <typename T>
void WorkflowMediator<T>::setExternalSystem(const std::string& name)
{
    externalSystem->setName(name);
}

template <typename T>
std::string WorkflowMediator<T>::getExternalSystem() const
{
    return externalSystem->getName();
}

template <typename T>
AbstractWorkItem<T>* WorkflowMediator<T>::getWorkItem(int id) const
{
    for (AbstractWorkItem<T>* item : workItems)
    {
        if (item->getId() == id)
        {
            return item;
        }
    }
    return nullptr;
}

template <typename T>
const std::vector<AbstractWorkItem<T>*>& WorkflowMediator<T>::getWorkItems() const
{
    return workItems;
}

template <typename T>
Iterator<T>* WorkflowMediator<T>::createIterator() const
{
    return new WorkItemIterator<T>(this);
}

template <typename T>
bool WorkflowMediator<T>::addDependency(int predecessorId, int successorId)
{
    if (predecessorId == successorId || getWorkItem(predecessorId) == nullptr ||
        getWorkItem(successorId) == nullptr)
    {
        return false;
    }

    std::vector<int>& successors = dependencies[predecessorId];
    for (std::vector<int>::const_iterator it = successors.begin(); it != successors.end(); ++it)
    {
        if (*it == successorId)
        {
            return false;
        }
    }

    successors.push_back(successorId);
    return true;
}

template <typename T>
void WorkflowMediator<T>::notify(AbstractWorkItem<T>* colleague)
{
    if (colleague == nullptr || colleague->getStateName() != "Completed")
    {
        return;
    }

    strategy->algorithm(colleague);
    std::cout << "  [Mediator] Telling " << externalSystem->getName() << " that " << colleague->getName() << " is complete" << std::endl;
    external->request();

    std::map<int, std::vector<int> >::const_iterator dependency = dependencies.find(colleague->getId());
    if (dependency == dependencies.end())
    {
        return;
    }

    for (std::vector<int>::const_iterator it = dependency->second.begin(); it != dependency->second.end(); ++it)
    {
        AbstractWorkItem<T>* successor = getWorkItem(*it);
        if (successor != nullptr && successor->getStateName() == "Created")
        {
            successor->handleState();
        }
    }
}

template <typename T>
void WorkflowMediator<T>::setStrategy(Strategy<T>* strategy)
{
    if (strategy == nullptr || strategy == this->strategy)
    {
        return;
    }
    delete this->strategy;
    this->strategy = strategy;
}

template <typename T>
int WorkflowMediator<T>::savePrototype(AbstractWorkItem<T>* item)
{
    if (item == nullptr)
    {
        return -1;
    }
    prototypes.addPrototype(item->clone(0, nullptr));
    return prototypes.getPrototypeCount() - 1;
}

template <typename T>
AbstractWorkItem<T>* WorkflowMediator<T>::createFromPrototype(int index, int id)
{
    AbstractWorkItem<T>* prototype = prototypes.getPrototype(index);
    if (prototype == nullptr || getWorkItem(id) != nullptr)
    {
        return nullptr;
    }
    AbstractWorkItem<T>* item = prototype->clone(id, this);
    addWorkItem(item);
    return item;
}

template class WorkflowMediator<int>;
