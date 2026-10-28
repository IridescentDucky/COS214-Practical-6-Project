#include "WorkItemIterator.h"
#include "WorkflowMediator.h"

WorkItemIterator::WorkItemIterator(const WorkflowMediator* collection)
    : currentIndex(0), collection(collection)
{
}

bool WorkItemIterator::hasNext() const
{
    return collection != nullptr && currentIndex < static_cast<int>(collection->workItems.size());
}

AbstractWorkItem* WorkItemIterator::next()
{
    if (!hasNext())
    {
        return nullptr;
    }
    return collection->workItems[currentIndex++];
}
