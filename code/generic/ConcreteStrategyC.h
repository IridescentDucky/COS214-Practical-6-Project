#ifndef ConcreteStrategyC_h
#define ConcreteStrategyC_h

#include "Strategy.h"

class ConcreteStrategyC : public Strategy {
public:
    ~ConcreteStrategyC() override = default;
    void algorithm() override;
};

#endif
