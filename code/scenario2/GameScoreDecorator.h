#ifndef GAMESCOREDECORATOR_H
#define GAMESCOREDECORATOR_H

#include "GameDecorator.h"


class GameScoreDecorator : public GameDecorator{

private:
    int bonusScore;
    int multiplier;
public:
    GameScoreDecorator(FileSystemComponent* component, int bonusScore);
    GameScoreDecorator(FileSystemComponent* component, int bonusScore, int multiplier);
    ~GameScoreDecorator();
    int getScore();

};


#endif