#ifndef WORKFLOWMEDIATOR_H
#define WORKFLOWMEDIATOR_H

#include <vector>

class AbstractWorkItem;

class WorkflowMediator
{
public:
    WorkflowMediator();
    ~WorkflowMediator();

    void addWorkItem(AbstractWorkItem* item);
    AbstractWorkItem* getWorkItem(int id) const;
    const std::vector<AbstractWorkItem*>& getWorkItems() const;

    void notify(AbstractWorkItem* colleague);

private:
    std::vector<AbstractWorkItem*> workItems;
};

#endif
