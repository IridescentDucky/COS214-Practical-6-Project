#include "ConcreteHandler.h"
#include "State.h"

template <typename T>
ConcreteHandler<T>::ConcreteHandler(string name, T condition) : TaskEscalationManager<T>(condition), name(name) {}

template <typename T>
void ConcreteHandler<T>::handleRequest(T a){    
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
ConcreteHandler<T>::~ConcreteHandler() {
    delete this->successor;

    this->successor = nullptr;
}

template <typename T>
void ConcreteHandler<T>::update() {

    if (this->workItem == nullptr) {
        return;
    }

    State<T>* currentState = this->workItem->getState();

    std::cout << name << " was notified that WorkItem has changed state to " << currentState->getName() << std::endl;

    handleRequest(this->condition);     //handleRequest takes in a T, condition is of type T
}

template class ConcreteHandler<int>;
