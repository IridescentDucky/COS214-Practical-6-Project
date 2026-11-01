#ifndef CONCRETESTRATEGYC_H
#define CONCRETESTRATEGYC_H

#include "Strategy.h"
#include "AbstractWorkItem.h"

/** @brief Scoring strategy that calculates a work item's lowest score. */
template <typename T>
class ConcreteStrategyC : public Strategy<T> {
    
public:
    /** @brief Destroys the strategy. */
    ~ConcreteStrategyC() override = default;
    /** @brief Calculates the lowest score for a work item.
     *  @param workItem Work item to evaluate.
     *  @return The lowest score.
     */
    double algorithm(AbstractWorkItem<T>* workItem) override;
};

#endif
