#ifndef DECORATOR_H
#define DECORATOR_H

#include "Component.h"
#include <iostream>


class Decorator : public Component{

public:

    Decorator(Component* component);
    virtual void operation() = 0;
    virtual ~Decorator();

protected:
    Component* component ;//component to deco
};

#endif