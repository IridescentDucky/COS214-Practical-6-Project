#include "Decorator.h"

Decorator::Decorator(Component* component){
    
    this->component = component;
}

Decorator::~Decorator(){

}

void Decorator::operation(){
    
    component->operation();
}