#include "ConcreteObserver.h"
#include "AbstractWorkItem.h"
#include "TaskEscalationManager.h"

#include "Observer.h"

template <typename T>
ConcreteObserver<T>::ConcreteObserver(AbstractWorkItem<T>* subject, TaskEscalationManager<T>* handler) : subject(subject), handler(handler) {

}

template <typename T>
ConcreteObserver<T>::~ConcreteObserver(){
    if (this->subject != nullptr) {
        this->subject->detach(this);
    }

}

template <typename T>
void ConcreteObserver<T>::update() {
    State<T>* currentState = this->subject->getState();  //get current state 

    // this->handler->handleRequest(this->subject, currentState);  //send request through chain
    // Handler only has one parameter handleRequest(T a);
}
