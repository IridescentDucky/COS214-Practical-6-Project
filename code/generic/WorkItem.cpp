#include "WorkItem.h"
#include "State.h"
#include "WorkflowMediator.h"
//#include "Observer.h"
#include "WorkItemMemento.h"

#include <iostream>
#include <string>

using namespace std;

template <typename T>
WorkItem<T>::WorkItem(int id, const std::string& name, int deadline, WorkflowMediator<T>* mediator)
    : AbstractWorkItem<T>(id, name, mediator), deadline(deadline), timeSpent(0)
{
}

template <typename T>
void WorkItem<T>::handleState()
{
    this->state->nextState(this);
}

template <typename T>
void WorkItem<T>::paused()
{
    this->state->paused(this);
}

template <typename T>
void WorkItem<T>::resume()
{
    this->state->resume(this);
}

template <typename T>
void WorkItem<T>::retry()
{
    this->state->retry(this);
}


template <typename T>
void WorkItem<T>::failed()
{
    this->state->failed(this);
}

template <typename T>
void WorkItem<T>::failedDelivery()
{
    this->state->failedDelivery(this);
}

template <typename T>
void WorkItem<T>::exception()
{
    this->state->exception(this);
}

template <typename T>
void WorkItem<T>::validate()
{
    this->state->validate(this);
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
State<T>* WorkItem<T>::getState() const
{
    return this->state;
}

//THIS GETS HANDLED BY ITS PARENT
// template <typename T>
// void WorkItem<T>::setState(State<T>* newState)
// {
//     if (newState == nullptr)
//     {
//         std::cout << "  [State] Cannot set a null state for " << this->name << std::endl;
//         return;
//     }
//     std::cout << "  [State] " << this->name << ": " << this->state->getName() << " -> " << newState->getName() << std::endl;
//     State<T>* old = this->state;
//     this->state = newState;
//     delete old;

//     notify();  //For Observer, if the state changes then notify the observers
// }

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
    if (this->mediator != nullptr)
    {
        this->mediator->notify(this);
    }
}

template <typename T>
WorkItemMemento<T>* WorkItem<T>::createMemento()
{
    std::cout << "[WorkItem] " << this->name << " creating snapshot of state: "
              << (this->state ? this->state->getName() : "None") << std::endl;
              
    return new WorkItemMemento<T>(this->state);
}

template <typename T>
void WorkItem<T>::setMemento(WorkItemMemento<T>* m)
{
    if (m == nullptr)
    {
        std::cout << "[WorkItem] " << this->name << " cannot restore from null memento." << std::endl;
        return;
    }

    State<T>* savedState = m->getState();
    if (savedState != nullptr)
    {
        std::cout << "[WorkItem] " << this->name << " restoring state from memento: "
                  << savedState->getName() << std::endl;
        this->setState(savedState);
    }
}

// template <typename T> // changed to display() and implemented in abstractworkitem
// void WorkItem<T>::operation(){

//     std::cout << "Execute WorkItem operation..." << std::endl;  //Decorator 
// }

// template <typename T>
// void WorkItem<T>::attach(Observer* observer){

//     observers.push_back(observer);
// }

// template <typename T>
// void WorkItem<T>::detach(Observer* observer){

//     for (std::vector<Observer*>::iterator it = observers.begin(); it != observers.end(); ++it){

//         if (*it == observer){

//             observers.erase(it);        //stole algo from Iterator slides hehe
//             break;
//         }
//     }
// }

// template <typename T>
// void WorkItem<T>::notify(){

//     for (Observer* observer : observers) {
        
//         if (observer != nullptr) {
//             observer->update();
//         }
//     }
// }

template class WorkItem<int>;
