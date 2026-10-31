#include "ConcreteCreator.h"
#include "WorkItem.h"

#include <iostream>


template <typename T>
AbstractWorkItem<T>* ConcreteCreator<T>::factoryMethod(int id, const std::string& name, int deadline, WorkflowMediator<T>* mediator){
    std::cout << "  [Factory] Creating WorkItem '" << name << "'" << std::endl;

    return new WorkItem<T>(id, name, deadline, mediator);
}

template class ConcreteCreator<int>;
