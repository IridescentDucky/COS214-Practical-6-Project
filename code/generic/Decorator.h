#ifndef DECORATOR_H
#define DECORATOR_H

#include "Component.h"
#include <iostream>


/** @brief Base decorator that forwards component operations. */
template <typename T>
class Decorator : public Component<T> {
public:

    /** @brief Wraps a component with decorator behavior.
     *  @param component Component being decorated.
     */
    Decorator(Component<T>* component);
    /** @brief Displays the wrapped component.
     *  @param indent Indentation level used for hierarchical output.
     */
    void display(int indent = 0);
    /** @brief Destroys the decorator. */
    virtual ~Decorator();

    /** @brief Gets the wrapped component's score. */
    int getScore();
    /** @brief Gets the wrapped component's time allowance. */
    int getTime();

protected:
    Component<T>* component ;//component to deco
};

#endif
