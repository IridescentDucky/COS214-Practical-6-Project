#ifndef CONCRETEDECORATORA_H
#define CONCRETEDECORATORA_H

#include "Decorator.h"

class ConcreteDecoratorA : public Decorator{

public:
    ConcreteDecoratorA(Component* component);
    void addFunctionalityA();
    void operation();
};


#endif