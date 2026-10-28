#include "ConcreteObserver.h"
#include "WorkItem.h"
#include "State.h"

ConcreteObserver::ConcreteObserver(WorkItem* item): item(item){

    if (this->item != nullptr) {

        this->item->attach(this);
    }
}

ConcreteObserver::~ConcreteObserver(){

    if (item != nullptr) {

        item->detach(this);
    }

}

void ConcreteObserver::update(){    //pull observer baby

    WorkItemState* currentState = item->getState();

    std::cout << "Observer notified" << std::endl;
    std::cout << "Current state: " << currentState->getName() << std::endl;
}