#include "WorkItem.h"
#include "State.h"
#include "WorkflowMediator.h"
#include "Observer.h"

#include <iostream>

AbstractWorkItem::AbstractWorkItem(int id, const std::string& name, WorkflowMediator* mediator)
    : id(id), name(name), state(new Created()), mediator(mediator)
{
}

AbstractWorkItem::~AbstractWorkItem()
{
    delete state;
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

WorkItem::WorkItem(int id, const std::string& name, int deadline, WorkflowMediator* mediator)
    : AbstractWorkItem(id, name, mediator), deadline(deadline), timeSpent(0)
{
}

void WorkItem::handleState()
{
    state->nextState(this);
}

void WorkItem::paused()
{
    state->paused(this);
}

void WorkItem::resume()
{
    state->resume(this);
}

void WorkItem::retry()
{
    state->retry(this);
}

void WorkItem::failed()
{
    state->failed(this);
}

void WorkItem::failedDelivery()
{
    state->failedDelivery(this);
}

void WorkItem::exception()
{
    state->exception(this);
}

void WorkItem::validate()
{
    state->validate(this);
}

void WorkItem::set(const std::string& data)
{
    this->data = data;
}

std::string WorkItem::get() const
{
    return data;
}

void WorkItem::addTimeSpent(int units)
{
    timeSpent += units;
}

WorkItemState* WorkItem::getState() const
{
    return state;
}

void WorkItem::setState(WorkItemState* newState)
{
    std::cout << "  [State] " << name << ": " << state->getName() << " -> " << newState->getName() << std::endl;
    WorkItemState* old = state;
    state = newState;
    delete old;

    notify();  //For Observer, if the state changes then notify the observers
}

bool WorkItem::isWithinDeadline() const
{
    return timeSpent <= deadline;
}

bool WorkItem::hasValidData() const
{
    return !data.empty();
}

void WorkItem::notifyWorkflow()
{
    mediator->notify(this);
}

WorkItemMemento* WorkItem::createMemento()
{
    std::cout << "[WorkItem] " << name << " creating snapshot of state: "
              << (state ? state->getName() : "None") << std::endl;
              
    return new WorkItemMemento(this->state);
}

void WorkItem::setMemento(WorkItemMemento* m)
{
    if (m == nullptr)
    {
        std::cout << "[WorkItem] " << name << " cannot restore from null memento." << std::endl;
        return;
    }

    WorkItemState* savedState = m->getState();
    if (savedState != nullptr)
    {
        std::cout << "[WorkItem] " << name << " restoring state from memento: "
                  << savedState->getName() << std::endl;
        this->setState(savedState);
    }
}

void AbstractWorkItem::operation(){

    std::cout << "Execute WorkItem operation..." << std::endl;  //Decorator 
}

void WorkItem::attach(Observer* observer){

    observers.push_back(observer);
}

void AbstractWorkItem::detach(Observer* observer){

    for (std::vector<Observer*>::iterator it = observers.begin(); it != observers.end(); ++it){

        if (*it == observer){

            observers.erase(it);        //stole algo from Iterator slides hehe
            break;
        }
    }
}

void AbstractWorkItem::notify(){

    for (Observer* observer : observers) {
        
        if (observer != nullptr) {
            observer->update();
        }
    }
}
