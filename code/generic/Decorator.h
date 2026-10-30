#ifndef DECORATOR_H
#define DECORATOR_H

#include "Component.h"
#include <iostream>


template <typename T>
class Decorator : public Component<T> {
public:

    Decorator(Component<T>* component);
    void display(int indent = 0);
    virtual ~Decorator();

    int getScore();
    int getTime();

protected:
    Component<T>* component ;//component to deco
};

#endif
