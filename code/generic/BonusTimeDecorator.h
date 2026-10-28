#ifndef BONUSTIMEDECORATOR_H
#define BONUSTIMEDECORATOR_H

#include "Decorator.h"

class BonusTimeDecorator : public Decorator {

private:
    int extraTime;

public:
    BonusTimeDecorator(Component* component, int extraTime);

    int getTime();
};

#endif