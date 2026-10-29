#ifndef CONCRETECREATOR_H
#define CONCRETECREATOR_H

#include "Creator.h"

template <typename T>
class ConcreteCreator : public Creator<T> {
protected:
    AbstractWorkItem<T>* factoryMethod();
};

#endif