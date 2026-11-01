#ifndef BONUSTIMEDECORATOR_H
#define BONUSTIMEDECORATOR_H

#include "Decorator.h"

/** @brief Decorator that adds a time allowance to a component. */
template <typename T>
class BonusTimeDecorator : public Decorator<T> {
private:
    int extraTime;

public:
    /** @brief Adds extra time to the wrapped component.
     *  @param component Component to decorate.
     *  @param extraTime Additional time units.
     */
    BonusTimeDecorator(Component<T>* component, int extraTime);

    /** @brief Gets the wrapped time allowance including the bonus.
     *  @return The decorated time.
     */
    int getTime();
};

#endif