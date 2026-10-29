#ifndef BONUSTIMEDECORATOR_H
#define BONUSTIMEDECORATOR_H

#include "Decorator.h"

template <typename T>
class BonusTimeDecorator : public Decorator<T> {
private:
    int extraTime;

public:
    BonusTimeDecorator(Component<T>* component, int extraTime);

    int getTime();
};

#endif