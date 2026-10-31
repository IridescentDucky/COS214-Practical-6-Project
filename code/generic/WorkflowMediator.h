#ifndef WORKFLOWMEDIATOR_H
#define WORKFLOWMEDIATOR_H

#include "AbstractWorkItem.h"
#include "Aggregate.h"
#include "PrototypeManager.h"

#include <vector>
#include <map>

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

    Iterator<T>* createIterator() const override;

private:
    friend class WorkItemIterator<T>;

    std::vector<AbstractWorkItem<T>*> workItems;
    std::map<int, std::vector<int> > dependencies;
    std::vector<TaskEscalationManager<T>*> escalations;
    Strategy<T>* strategy;
    Adaptee* externalSystem;
    Target* external;
    PrototypeManager<T> prototypes;
};

#endif
