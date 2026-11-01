#ifndef BONUSSCOREDECORATOR_H
#define BONUSSCOREDECORATOR_H

#include "Decorator.h"
#include "Component.h"

/** @brief Decorator that adds a bonus to a component's score. */
template <typename T>
class BonusScoreDecorator : public Decorator<T> {
private:
    int bonusScore;
    int multiplier;

public:
    /** @brief Adds a fixed bonus to the wrapped component's score.
     *  @param component Component to decorate.
     *  @param bonusScore Score to add.
     */
    BonusScoreDecorator(Component<T>* component,int bonusScore);
    /** @brief Adds a multiplied bonus to the wrapped component's score.
     *  @param component Component to decorate.
     *  @param bonusScore Base score bonus.
     *  @param multiplier Factor applied to the bonus.
     */
    BonusScoreDecorator(Component<T>* component,int bonusScore, int multiplier);//overloaded 
    /** @brief Gets the wrapped score including this decorator's bonus.
     *  @return The decorated score.
     */
    int getScore();
};

#endif