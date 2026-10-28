#include "ConcreteDecoratorB.h"

ConcreteDecoratorB::ConcreteDecoratorB(Component* component) : Decorator(component){

}

void ConcreteDecoratorB::addFunctionalityB(){

    std::cout << "Adding functionality B to the WorkItem..." << std::endl;
}

void ConcreteDecoratorB::operation(){

    component->operation();

    addFunctionalityB();

}