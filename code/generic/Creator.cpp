#include "Creator.h"

template <typename T>
Creator<T>::~Creator(){

    //im not delting AbstractWorkItem here, its def causing mem leaks, might default it
}

template <typename T>
AbstractWorkItem<T>* Creator<T>::createWorkItem(int id, const std::string& name, int deadline, WorkflowMediator<T>* mediator){

    return factoryMethod(id, name, deadline, mediator); //followed Chocolate example in lecture slides
}

template class Creator<int>;
