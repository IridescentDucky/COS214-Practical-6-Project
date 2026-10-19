#include "WorkItemMemento.h"
#include <iostream>

WorkItemMemento::WorkItemMemento(WorkItemState* s){
    
    this->state = s;
}

WorkItemState* WorkItemMemento::getState() const{
    
    std::cout << "[WorkItemMemento] returning state: " << this->state << std::endl;
    return this->state;
}

void WorkItemMemento::setState(WorkItemState* s){
    
    std::cout << "[WorkItemMemento] setting new state: " << s << " from state: " << this->state << std::endl;
    this->state = s;
}
