#ifndef CONCRETEDECORATORB_H
#define CONCRETEDECORATORB_H

#include "Decorator.h"

class ConcreteDecoratorB : public Decorator{

public:

    ConcreteDecoratorB(Component* component);
    void addFunctionalityB();
    void operation();
};


#endif