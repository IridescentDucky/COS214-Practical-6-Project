#include "WorkItemMemento.h"
#include "State.h"
#include <iostream>

template <typename T>
WorkItemMemento<T>::WorkItemMemento(State<T>* s){
    this->state = s != nullptr ? s->clone() : nullptr;
}

template <typename T>
WorkItemMemento<T>::~WorkItemMemento(){
    delete this->state;
}

template <typename T>
State<T>* WorkItemMemento<T>::getState() const{
    std::cout << "[WorkItemMemento] returning a copy of state: "
              << (this->state != nullptr ? this->state->getName() : "None") << std::endl;

    return this->state != nullptr ? this->state->clone() : nullptr;
}


template <typename T>
void WorkItemMemento<T>::setState(State<T>* s){
    std::cout << "[WorkItemMemento] setting new state: " << s << " from state: " << this->state << std::endl;
    delete this->state;

    this->state = s != nullptr ? s->clone() : nullptr;
}
