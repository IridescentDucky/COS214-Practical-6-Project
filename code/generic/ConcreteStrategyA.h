#ifndef ConcreteStrategyA_h
#define ConcreteStrategyA_h

#include "Strategy.h"

class ConcreteStrategyA : public Strategy {
public:
    ~ConcreteStrategyA() override = default;
    void algorithm() override;
};

#endif
