#include "AbstractWorkItem.h"

AbstractWorkItem::AbstractWorkItem(int id, const std::string& name, WorkflowMediator* mediator)
    : id(id), name(name), state(new Created()), mediator(mediator)
{
}

int AbstractWorkItem::getId() const
{
    return id;
}

std::string AbstractWorkItem::getName() const
{
    return name;
}

std::string AbstractWorkItem::getStateName() const
{
    return state->getName();
}


AbstractWorkItem::~AbstractWorkItem(){

    delete state;

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
