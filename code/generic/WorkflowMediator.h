#ifndef WORKFLOWMEDIATOR_H
#define WORKFLOWMEDIATOR_H

#include <vector>
#include <map>

class AbstractWorkItem;

class WorkflowMediator
{
public:
    WorkflowMediator();
    ~WorkflowMediator();

    void addWorkItem(AbstractWorkItem* item);
    AbstractWorkItem* getWorkItem(int id) const;
    const std::vector<AbstractWorkItem*>& getWorkItems() const;
    bool addDependency(int predecessorId, int successorId);

    void notify(AbstractWorkItem* colleague);

private:
    std::vector<AbstractWorkItem*> workItems;
    std::map<int, std::vector<int> > dependencies;
};

#endif
