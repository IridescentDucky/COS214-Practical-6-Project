#include "BonusScoreDecorator.h"

template <typename T>
BonusScoreDecorator<T>::BonusScoreDecorator(Component<T>* component, int bonusScore) : Decorator<T>(component), bonusScore(bonusScore), multiplier(1){

}

template <typename T>
BonusScoreDecorator<T>::BonusScoreDecorator(Component<T>* component, int bonusScore, int multiplier): Decorator<T>(component), bonusScore(bonusScore), multiplier(multiplier){

}

template <typename T>
int BonusScoreDecorator<T>::getScore(){
    return (this->component->getScore() + this->bonusScore) * multiplier;
}