#ifndef WORKITEMITERATOR_H
#define WORKITEMITERATOR_H

#include "Iterator.h"

template <typename T>
class WorkflowMediator;

template <typename T>
class WorkItemIterator : public Iterator<T>
{
public:
    explicit WorkItemIterator(const WorkflowMediator<T>* collection);

    bool hasNext() const override;
    AbstractWorkItem<T>* next() override;

private:
    int currentIndex;
    const WorkflowMediator<T>* collection;
};

#endif
