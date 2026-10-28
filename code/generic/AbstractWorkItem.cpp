#include "AbstractWorkItem.h"

AbstractWorkItem::~AbstractWorkItem(){

    //IM NOT GETTING MY PAWS DIRTY WITH THIS ONE...YET, ill wait for everyone to add their things first
}


void AbstractWorkItem::attach(Observer* observer) {

    observers.push_back(observer);
}

void AbstractWorkItem::detach(Observer* observer) {

    for (std::vector<Observer*>::iterator it = observers.begin(); it != observers.end(); ++it){

        if (*it == observer){

            observers.erase(it);        //stole algo from Iterator slides hehe
            break;
        }
    }
}

void AbstractWorkItem::notify() {

    for (Observer* observer : observers) {
        observer->update();
    }
}

void AbstractWorkItem::setState(State* newState) {

    if (state == newState) {
        return;
    }

    this->state = newState;
    notify();
}

State* AbstractWorkItem::getState(){

    return this->state;
}