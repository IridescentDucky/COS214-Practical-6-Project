#include "ConcreteHandlerB.h"
#include "AbstractWorkItem.h"
#include "State.h"

template <typename T>
ConcreteHandlerB<T>::ConcreteHandlerB(string name, T condition) : TaskEscalationManager<T>(condition), name(name) {}

template <typename T>
void ConcreteHandlerB<T>::handleRequest(T a){    
    if(a < this->condition) { // could have multiple classes for the differing types of conditions (eg. a class for <, >, ==, <=, >=)
        std::cout << name << " handled the request" << std::endl;
    }
    else if(this->successor != nullptr){
        std::cout << name << " passed the request on" << std::endl;
        this->successor->handleRequest(a);
    }
    else{
        std::cout << "The request could not be handled" << std::endl;
    }
        
    return;
}

template <typename T>
void ConcreteHandlerB<T>::update() {

    if (this->workItem == nullptr) {
        return;
    }

    State<T>* currentState = this->workItem->getState();
    int overdue = this->workItem->getOverdue();

    std::cout << name << " was notified that " << this->workItem->getName() << " is " << currentState->getName();
    if (overdue > 0) {
        std::cout << " and " << overdue << " time unit(s) overdue" << std::endl;
        handleRequest(static_cast<T>(overdue));
    }
    else {
        std::cout << std::endl;
    }
}

template class ConcreteHandlerB<int>;
