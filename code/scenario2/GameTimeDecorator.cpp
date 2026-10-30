#include "GameTimeDecorator.h"
   
GameTimeDecorator::GameTimeDecorator(FileSystemComponent* component, int extraTime) : GameDecorator(component), extraTime(extraTime) {

}

GameTimeDecorator::~GameTimeDecorator(){

}

int GameTimeDecorator::getTime(){
    
    return component->getTime() + extraTime;
}
