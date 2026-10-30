#ifndef CONCRETESTRATEGYC_H
#define CONCRETESTRATEGYC_H

#include "Strategy.h"
#include "AbstractWorkItem.h"

template <typename T>
class ConcreteStrategyC : public Strategy<T> {
    
public:
    ~ConcreteStrategyC() override = default;
    double algorithm(AbstractWorkItem<T>* workItem) override;
};

#endif
