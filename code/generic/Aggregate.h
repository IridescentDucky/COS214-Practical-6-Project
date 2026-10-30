#ifndef AGGREGATE_H
#define AGGREGATE_H

template <typename T>
class Iterator;

template <typename T>
class Aggregate
{
public:
    virtual ~Aggregate()
    {
    }

    virtual Iterator<T>* createIterator() const = 0;
};

#endif
