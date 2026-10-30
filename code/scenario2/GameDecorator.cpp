#include "GameDecorator.h"

GameDecorator::GameDecorator(FileSystemComponent* component) : component(component) {}

GameDecorator::~GameDecorator() {}

int GameDecorator::getScore() {

    return component->getScore();

}

int GameDecorator::getTime() {

    return component->getTime();
    
}