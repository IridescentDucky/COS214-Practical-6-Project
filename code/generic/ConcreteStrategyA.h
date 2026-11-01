#ifndef CONCRETESTRATEGYA_H
#define CONCRETESTRATEGYA_H

#include "Strategy.h"
#include "AbstractWorkItem.h" // for access to TaskRecord and getTask()

/** @brief Scoring strategy that calculates a work item's average score. */
template <typename T>
class ConcreteStrategyA : public Strategy<T> {
    
public:
    /** @brief Destroys the strategy. */
    ~ConcreteStrategyA() override = default;
    /** @brief Calculates the average score for a work item.
     *  @param item Work item to evaluate.
     *  @return The average score.
     */
    double algorithm(AbstractWorkItem<T>* item) override;
};

#endif
