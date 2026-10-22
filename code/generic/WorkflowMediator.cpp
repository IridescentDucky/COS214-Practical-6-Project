#include "WorkflowMediator.h"
#include "WorkItem.h"

WorkflowMediator::WorkflowMediator()
{
}

WorkflowMediator::~WorkflowMediator()
{
    for (AbstractWorkItem* item : workItems)
    {
        delete item;
    }
}

void WorkflowMediator::addWorkItem(AbstractWorkItem* item)
{
    if (item != nullptr && getWorkItem(item->getId()) == nullptr)
    {
        workItems.push_back(item);
    }
}

AbstractWorkItem* WorkflowMediator::getWorkItem(int id) const
{
    for (AbstractWorkItem* item : workItems)
    {
        if (item->getId() == id)
        {
            return item;
        }
    }
    return nullptr;
}

const std::vector<AbstractWorkItem*>& WorkflowMediator::getWorkItems() const
{
    return workItems;
}

bool WorkflowMediator::addDependency(int predecessorId, int successorId)
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

void WorkflowMediator::notify(AbstractWorkItem* colleague)
{
    if (colleague == nullptr || colleague->getStateName() != "Completed")
    {
        return;
    }

    std::map<int, std::vector<int> >::const_iterator dependency = dependencies.find(colleague->getId());
    if (dependency == dependencies.end())
    {
        return;
    }

    for (std::vector<int>::const_iterator it = dependency->second.begin(); it != dependency->second.end(); ++it)
    {
        AbstractWorkItem* successor = getWorkItem(*it);
        if (successor != nullptr && successor->getStateName() == "Created")
        {
            successor->handleState();
        }
    }
}
