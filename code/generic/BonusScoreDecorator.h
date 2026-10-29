#ifndef BONUSSCOREDECORATOR_H
#define BONUSSCOREDECORATOR_H

#include "Decorator.h"
#include "Component.h"

template <typename T>
class BonusScoreDecorator : public Decorator<T> {
private:
    int bonusScore;
    int multiplier;

public:
    BonusScoreDecorator(Component<T>* component,int bonusScore);
    BonusScoreDecorator(Component<T>* component,int bonusScore, int multiplier);//overloaded 
    int getScore();
};

#endif