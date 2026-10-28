#include "Decorator.h"

Decorator::Decorator(Component* component){
    
    this->component = component;
}

Decorator::~Decorator(){

}

void Decorator::operation(){
    
    component->operation();
}

int Decorator::getScore() {
    return component->getScore();
}

int Decorator::getTime() {
    return component->getTime();
}
