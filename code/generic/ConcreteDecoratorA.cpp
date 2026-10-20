#include "ConcreteDecoratorA.h"

ConcreteDecoratorA::ConcreteDecoratorA(Component* component) : Decorator(component){

}

void ConcreteDecoratorA::addFunctionalityA(){

    std::cout << "Adding functionality A to the WorkItem..." << std::endl;
}

void ConcreteDecoratorA::operation(){

    component->operation();

    addFunctionalityA();

}