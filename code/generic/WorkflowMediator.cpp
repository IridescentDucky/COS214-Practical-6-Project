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
    workItems.push_back(item);
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

void WorkflowMediator::notify(AbstractWorkItem*)
{
}
