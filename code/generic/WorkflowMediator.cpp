#include "WorkflowMediator.h"
#include "WorkItem.h"
#include "WorkItemIterator.h"

template <typename T>
WorkflowMediator<T>::WorkflowMediator()
{
}

template <typename T>
WorkflowMediator<T>::~WorkflowMediator()
{
    for (AbstractWorkItem<T>* item : workItems)
    {
        delete item;
    }
}

template <typename T>
void WorkflowMediator<T>::addWorkItem(AbstractWorkItem<T>* item)
{
    if (item != nullptr && getWorkItem(item->getId()) == nullptr)
    {
        workItems.push_back(item);
    }
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

template class WorkflowMediator<int>;
