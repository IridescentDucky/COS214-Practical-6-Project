#ifndef ConcreteStrategyB_h
#define ConcreteStrategyB_h

#include "Strategy.h"

class ConcreteStrategyB : public Strategy {
public:
    ~ConcreteStrategyB() override = default;
    void algorithm() override;
};

#endif
