#ifndef ITERATOR_H
#define ITERATOR_H

template <typename T>
class AbstractWorkItem;

/** @brief Abstract forward iterator over work items. */
template <typename T>
class Iterator
{
public:
    /** @brief Destroys the iterator through its base interface. */
    virtual ~Iterator()
    {
    }

    /** @brief Checks whether another work item is available.
     *  @return True if next() can return an item.
     */
    virtual bool hasNext() const = 0;
    /** @brief Returns the next work item.
     *  @return The next item, or null when exhausted.
     */
    virtual AbstractWorkItem<T>* next() = 0;
};

#endif
