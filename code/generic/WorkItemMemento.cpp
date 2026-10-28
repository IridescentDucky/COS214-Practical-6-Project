#include "WorkItemMemento.h"
#include "State.h"
#include <iostream>

WorkItemMemento::WorkItemMemento(WorkItemState* s){
    this->state = s != nullptr ? s->clone() : nullptr;
}

WorkItemMemento::~WorkItemMemento(){
    delete state;
}

WorkItemState* WorkItemMemento::getState() const{
    
    std::cout << "[WorkItemMemento] returning a copy of state: "
              << (this->state != nullptr ? this->state->getName() : "None") << std::endl;
    return this->state != nullptr ? this->state->clone() : nullptr;
}

void WorkItemMemento::setState(WorkItemState* s){
    
    std::cout << "[WorkItemMemento] setting new state: " << s << " from state: " << this->state << std::endl;
    delete this->state;
    this->state = s != nullptr ? s->clone() : nullptr;
}
