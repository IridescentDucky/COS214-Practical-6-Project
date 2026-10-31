#ifndef WORKFLOWMEDIATOR_H
#define WORKFLOWMEDIATOR_H

#include "AbstractWorkItem.h"
#include "PrototypeManager.h"
#include "Aggregate.h"

#include <vector>
#include <map>

template <typename T>
class AbstractWorkItem;

template <typename T>
class WorkItemIterator;

template <typename T>
class WorkflowMediator : public Aggregate<T> {
public:
    WorkflowMediator();
    ~WorkflowMediator();

    void addWorkItem(AbstractWorkItem<T>* item);
    AbstractWorkItem<T>* getWorkItem(int id) const;
    const std::vector<AbstractWorkItem<T>*>& getWorkItems() const;
    bool addDependency(int predecessorId, int successorId);

    void notify(AbstractWorkItem<T>* colleague);

    Iterator<T>* createIterator() const override;

    PrototypeManager<T>* pm; // if private, then additional functions must be added to mediator
private:
    friend class WorkItemIterator<T>;

    std::vector<AbstractWorkItem<T>*> workItems;
    std::map<int, std::vector<int> > dependencies;
};

#endif
