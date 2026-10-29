#include "WorkItem.h"
#include "State.h"
#include "WorkflowMediator.h"
#include "Observer.h"
#include "WorkItemMemento.h"

#include <iostream>
#include <string>

using namespace std;

template <typename T>
WorkItem<T>::WorkItem(int id, const std::string& name, int deadline, WorkflowMediator<T>* mediator)
    : AbstractWorkItem(id, name, mediator), deadline(deadline), timeSpent(0)
{
}

template <typename T>
void WorkItem<T>::handleState()
{
    state->nextState(this);
}

template <typename T>
void WorkItem<T>::paused()
{
    state->paused(this);
}

template <typename T>
void WorkItem<T>::resume()
{
    state->resume(this);
}

template <typename T>
void WorkItem<T>::retry()
{
    state->retry(this);
}


template <typename T>
void WorkItem<T>::failed()
{
    state->failed(this);
}

template <typename T>
void WorkItem<T>::failedDelivery()
{
    state->failedDelivery(this);
}

template <typename T>
void WorkItem<T>::exception()
{
    state->exception(this);
}

template <typename T>
void WorkItem<T>::validate()
{
    state->validate(this);
}

template <typename T>
void WorkItem<T>::set(const std::string& data)
{
    this->data = data;
}

template <typename T>
std::string WorkItem<T>::get() const
{
    return data;
}

template <typename T>
void WorkItem<T>::addTimeSpent(int units)
{
    timeSpent += units;
}


template <typename T>
WorkItemState<T>* WorkItem<T>::getState() const
{
    return state;
}

template <typename T>
void WorkItem<T>::setState(WorkItemState* newState)
{
    if (newState == nullptr)
    {
        std::cout << "  [State] Cannot set a null state for " << name << std::endl;
        return;
    }
    std::cout << "  [State] " << name << ": " << state->getName() << " -> " << newState->getName() << std::endl;
    WorkItemState* old = state;
    state = newState;
    delete old;

    notify();  //For Observer, if the state changes then notify the observers
}

template <typename T>
bool WorkItem<T>::isWithinDeadline() const
{
    return timeSpent <= deadline;
}

template <typename T>
bool WorkItem<T>::hasValidData() const
{
    return !data.empty();
}

template <typename T>
void WorkItem<T>::notifyWorkflow()
{
    if (mediator != nullptr)
    {
        mediator->notify(this);
    }
}

template <typename T>
WorkItemMemento* WorkItem<T>::createMemento()
{
    std::cout << "[WorkItem] " << name << " creating snapshot of state: "
              << (state ? state->getName() : "None") << std::endl;
              
    return new WorkItemMemento(this->state);
}

template <typename T>
void WorkItem<T>::setMemento(WorkItemMemento* m)
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

// template <typename T> // changed to display() and implemented in abstractworkitem
// void WorkItem<T>::operation(){

//     std::cout << "Execute WorkItem operation..." << std::endl;  //Decorator 
// }

template <typename T>
void WorkItem<T>::attach(Observer* observer){

    observers.push_back(observer);
}

template <typename T>
void WorkItem<T>::detach(Observer* observer){

    for (std::vector<Observer*>::iterator it = observers.begin(); it != observers.end(); ++it){

        if (*it == observer){

            observers.erase(it);        //stole algo from Iterator slides hehe
            break;
        }
    }
}

template <typename T>
void WorkItem<T>::notify(){

    for (Observer* observer : observers) {
        
        if (observer != nullptr) {
            observer->update();
        }
    }
}