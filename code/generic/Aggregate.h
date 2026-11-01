#ifndef AGGREGATE_H
#define AGGREGATE_H

template <typename T>
class Iterator;

/** @brief Provides iterator creation for a collection of work items. */
template <typename T>
class Aggregate
{
public:
    /** @brief Destroys the aggregate through its base interface. */
    virtual ~Aggregate()
    {
    }

    /** @brief Creates an iterator over the aggregate.
     *  @return A newly allocated iterator.
     */
    virtual Iterator<T>* createIterator() const = 0;
};

#endif
