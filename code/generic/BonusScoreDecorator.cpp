#include "BonusScoreDecorator.h"

BonusScoreDecorator::BonusScoreDecorator(Component* component, int bonusScore) : Decorator(component), bonusScore(bonusScore), multiplier(1){

}

BonusScoreDecorator::BonusScoreDecorator(Component* component, int bonusScore, int multiplier): Decorator(component), bonusScore(bonusScore), multiplier(multiplier){

}

int BonusScoreDecorator::getScore(){

    return (component->getScore() + bonusScore) * multiplier;
}