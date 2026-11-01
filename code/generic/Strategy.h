#ifndef STRATEGY_H
#define STRATEGY_H

template <typename T>
class AbstractWorkItem;

/** @brief Strategy interface for calculating a work-item statistic. */
template <typename T>
class Strategy {
    
public:
    /** @brief Destroys the strategy through its base interface. */
    virtual ~Strategy() = default;
    /** @brief Calculates a statistic for a work item.
     *  @param item Work item to evaluate.
     *  @return The calculated statistic.
     */
    virtual double algorithm(AbstractWorkItem<T>* item) = 0;
};

#endif
