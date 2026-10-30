#include "GameScoreDecorator.h"


GameScoreDecorator::GameScoreDecorator(FileSystemComponent* component, int bonusScore) : GameDecorator(component), bonusScore(bonusScore), multiplier(1) {

}

GameScoreDecorator::GameScoreDecorator(FileSystemComponent* component, int bonusScore, int multiplier) : GameDecorator(component), bonusScore(bonusScore), multiplier(multiplier) {

}

GameScoreDecorator::~GameScoreDecorator(){

}

int GameScoreDecorator::getScore(){
    
     return (component->getScore() + bonusScore) * multiplier;
}