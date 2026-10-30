#ifndef CONCRETESTRATEGYA_H
#define CONCRETESTRATEGYA_H

#include "Strategy.h"
#include "AbstractWorkItem.h" // for access to TaskRecord and getTask()

template <typename T>
class ConcreteStrategyA : public Strategy<T> {
    
public:
    ~ConcreteStrategyA() override = default;
    double algorithm(AbstractWorkItem<T>* item) override;
};

#endif
