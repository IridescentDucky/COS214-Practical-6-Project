#ifndef CONCRETESTRATEGYB_H
#define CONCRETESTRATEGYB_H

#include "Strategy.h"
#include "AbstractWorkItem.h"

/** @brief Scoring strategy that calculates a work item's highest score. */
template <typename T>
class ConcreteStrategyB : public Strategy<T> {
    
public:
    /** @brief Destroys the strategy. */
    ~ConcreteStrategyB() override = default;
    /** @brief Calculates the highest score for a work item.
     *  @param item Work item to evaluate.
     *  @return The highest score.
     */
    double algorithm(AbstractWorkItem<T>* item) override;
};

#endif
