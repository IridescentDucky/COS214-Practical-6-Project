#ifndef STRATEGY_H
#define STRATEGY_H

class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void algorithm() = 0;
};

#endif
