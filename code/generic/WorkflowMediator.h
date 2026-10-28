#ifndef WORKFLOWMEDIATOR_H
#define WORKFLOWMEDIATOR_H

#include "Aggregate.h"

#include <vector>
#include <map>

class AbstractWorkItem;

class WorkflowMediator : public Aggregate
{
public:
    WorkflowMediator();
    ~WorkflowMediator();

    void addWorkItem(AbstractWorkItem* item);
    AbstractWorkItem* getWorkItem(int id) const;
    bool addDependency(int predecessorId, int successorId);

    void notify(AbstractWorkItem* colleague);

    Iterator* createIterator() const override;

private:
    friend class WorkItemIterator;

    std::vector<AbstractWorkItem*> workItems;
    std::map<int, std::vector<int> > dependencies;
};

#endif
