#ifndef CONCRETECREATOR_H
#define CONCRETECREATOR_H

#include "Creator.h"

template <typename T>
class ConcreteCreator : public Creator<T> {
protected:
    AbstractWorkItem<T>* factoryMethod(int id, const std::string& name, int deadline, WorkflowMediator<T>* mediator);
};

#endif