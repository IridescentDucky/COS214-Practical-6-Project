#ifndef WORKITEMITERATOR_H
#define WORKITEMITERATOR_H

#include "Iterator.h"

class WorkflowMediator;

class WorkItemIterator : public Iterator
{
public:
    explicit WorkItemIterator(const WorkflowMediator* collection);

    bool hasNext() const override;
    AbstractWorkItem* next() override;

private:
    int currentIndex;
    const WorkflowMediator* collection;
};

#endif
