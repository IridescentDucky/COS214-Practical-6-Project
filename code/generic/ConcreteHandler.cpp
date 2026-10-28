#include "ConcreteHandler.h"

template <typename T>
ConcreteHandler<T>::ConcreteHandler(string name, T condition) : TaskEscalationManager(condition), name(name) {}

template <typename T>
void ConcreteHandler<T>::handleRequest(T a){    
    if(a < this->condition){
        std::cout << name << " handled the request" << std::endl;
    }
    else if(this->successor != nullptr){
        std::cout << name << " passed the request" << std::endl;
        this->successor->handleRequest();
    }
    else{
        std::cout << "The request could not be handled" << std::endl;
    }
        
    return;
}

template <typename T>
ConcreteHandler<T>::~ConcreteHandler() {
    delete successor;

    successor = nullptr;
}
