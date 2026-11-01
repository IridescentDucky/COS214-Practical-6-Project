#ifndef WORKFLOWMEDIATOR_H
#define WORKFLOWMEDIATOR_H

#include "AbstractWorkItem.h"
#include "Aggregate.h"
#include "PrototypeManager.h"

#include <vector>
#include <map>
#include <string>
#include <utility>

template <typename T>
class AbstractWorkItem;

template <typename T>
class WorkItemIterator;

template <typename T>
class Strategy;

template <typename T>
class TaskEscalationManager;

class Target;
class Adaptee;

template <typename T>
class WorkflowMediator : public Aggregate<T> {
public:
    WorkflowMediator();
    ~WorkflowMediator();
    WorkflowMediator(const WorkflowMediator&) = delete;
    WorkflowMediator& operator=(const WorkflowMediator&) = delete;

    void addWorkItem(AbstractWorkItem<T>* item);
    AbstractWorkItem<T>* getWorkItem(int id) const;
    const std::vector<AbstractWorkItem<T>*>& getWorkItems() const;
    bool addDependency(int predecessorId, int successorId);

    void notify(AbstractWorkItem<T>* colleague);

    void setStrategy(Strategy<T>* strategy);
    int savePrototype(AbstractWorkItem<T>* item);
    AbstractWorkItem<T>* createFromPrototype(int index, int id);
    bool setEscalationLevels(const std::vector<std::pair<std::string, T> >& levels);
    const std::vector<std::pair<std::string, T> >& getEscalationLevels() const;
    void setExternalSystem(const std::string& name);
    std::string getExternalSystem() const;

    Iterator<T>* createIterator() const override;
private:
    friend class WorkItemIterator<T>;

    TaskEscalationManager<T>* createChain() const;

    std::vector<AbstractWorkItem<T>*> workItems;
    std::map<int, std::vector<int> > dependencies;
    std::vector<TaskEscalationManager<T>*> escalations;
    std::vector<std::pair<std::string, T> > levels;
    Strategy<T>* strategy;
    Adaptee* externalSystem;
    Target* external;
    PrototypeManager<T> prototypes;
};

#endif
