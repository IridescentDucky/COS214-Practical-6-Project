#ifndef ITERATOR_H
#define ITERATOR_H

class AbstractWorkItem;

class Iterator
{
public:
    virtual ~Iterator()
    {
    }

    virtual bool hasNext() const = 0;
    virtual AbstractWorkItem* next() = 0;
};

#endif
