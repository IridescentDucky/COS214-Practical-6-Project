#include "ConcreteObserver.h"
#include "AbstractWorkItem.h"
#include "Handler.h"

ConcreteObserver::ConcreteObserver(AbstractWorkItem* subject, Handler* handler) : subject(subject), handler(handler) {

}

ConcreteObserver::~ConcreteObserver(){

    if (item != nullptr) {

        item->detach(this);
    }

}

void ConcreteObserver::update() {
    State* currentState = subject->getState();  //get current state 

    
    handler->handleRequest(subject, currentState);  //send request through chain
}
