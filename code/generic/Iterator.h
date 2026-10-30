#ifndef ITERATOR_H
#define ITERATOR_H

template <typename T>
class AbstractWorkItem;

template <typename T>
class Iterator
{
public:
    virtual ~Iterator()
    {
    }

    virtual bool hasNext() const = 0;
    virtual AbstractWorkItem<T>* next() = 0;
};

#endif
