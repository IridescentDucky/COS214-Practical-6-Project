#ifndef GAMETIMEDECORATOR_H
#define GAMETIMEDECORATOR_H

#include "GameDecorator.h"


class GameTimeDecorator : public GameDecorator{

private:
    int extraTime;
public:
    GameTimeDecorator(FileSystemComponent* component, int extraTime);
    ~GameTimeDecorator();
    int getTime();

};


#endif