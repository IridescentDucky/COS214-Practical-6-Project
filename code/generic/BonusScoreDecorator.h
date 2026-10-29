#ifndef BONUSSCOREDECORATOR_H
#define BONUSSCOREDECORATOR_H

#include "Decorator.h"

class BonusScoreDecorator : public Decorator {

private:
    int bonusScore;
    int multiplier;

public:
    BonusScoreDecorator(Component* component,int bonusScore);
    BonusScoreDecorator(Component* component,int bonusScore, int multiplier);//overloaded 
    int getScore();
};

#endif