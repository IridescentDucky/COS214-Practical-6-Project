#ifndef CONCRETESTRATEGYB_H
#define CONCRETESTRATEGYB_H

#include "Strategy.h"
#include "AbstractWorkItem.h"

template <typename T>
class ConcreteStrategyB : public Strategy<T> {
    
public:
    ~ConcreteStrategyB() override = default;
    double algorithm(AbstractWorkItem<T>* item) override;
};

#endif
