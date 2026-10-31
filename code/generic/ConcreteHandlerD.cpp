#include "ConcreteHandlerD.h"
#include "AbstractWorkItem.h"
#include "State.h"

template <typename T>
ConcreteHandlerD<T>::ConcreteHandlerD(string name, T condition) : TaskEscalationManager<T>(condition), name(name) {}

template <typename T>
void ConcreteHandlerD<T>::handleRequest(T a){    
    if(a <= this->condition) { 
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
void ConcreteHandlerD<T>::update() {

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

template class ConcreteHandlerD<int>;
