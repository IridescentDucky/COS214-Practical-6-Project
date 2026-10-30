#include "WorkItemIterator.h"
#include "WorkflowMediator.h"

template <typename T>
WorkItemIterator<T>::WorkItemIterator(const WorkflowMediator<T>* collection)
    : currentIndex(0), collection(collection)
{
}

template <typename T>
bool WorkItemIterator<T>::hasNext() const
{
    return collection != nullptr && currentIndex < static_cast<int>(collection->workItems.size());
}

template <typename T>
AbstractWorkItem<T>* WorkItemIterator<T>::next()
{
    if (!hasNext())
    {
        return nullptr;
    }
    return collection->workItems[currentIndex++];
}
