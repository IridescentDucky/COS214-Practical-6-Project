#ifndef WORKITEMITERATOR_H
#define WORKITEMITERATOR_H

#include "Iterator.h"

template <typename T>
class WorkflowMediator;

/** @brief Iterates through the work items registered with a mediator. */
template <typename T>
class WorkItemIterator : public Iterator<T>
{
public:
    /** @brief Creates an iterator for a mediator's work-item collection.
     *  @param collection Mediator whose items are traversed.
     */
    explicit WorkItemIterator(const WorkflowMediator<T>* collection);

    /** @brief Checks whether another item is available. */
    bool hasNext() const override;
    /** @brief Returns the next work item. */
    AbstractWorkItem<T>* next() override;

private:
    int currentIndex;
    const WorkflowMediator<T>* collection;
};

#endif
