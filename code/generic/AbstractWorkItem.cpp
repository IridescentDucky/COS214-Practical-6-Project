#include "AbstractWorkItem.h"

template <typename T>
AbstractWorkItem<T>::AbstractWorkItem(int id, const std::string& name, WorkflowMediator* mediator)
    : id(id), name(name), state(new Created()), mediator(mediator)
{
}

template <typename T>
int AbstractWorkItem<T>::getId() const
{
    return id;
}

template <typename T>
std::string AbstractWorkItem<T>::getName() const
{
    return name;
}

template <typename T>
std::string AbstractWorkItem<T>::getStateName() const
{
    return state->getName();
}


template <typename T>
AbstractWorkItem<T>::~AbstractWorkItem(){

    delete state;

    //IM NOT GETTING MY PAWS DIRTY WITH THIS ONE...YET, ill wait for everyone to add their things first
    // It's easy to do - trust...
}


template <typename T>
void AbstractWorkItem<T>::attach(Observer* observer) {

    observers.push_back(observer);
}

template <typename T>
void AbstractWorkItem<T>::detach(Observer* observer) {

    for (std::vector<Observer*>::iterator it = observers.begin(); it != observers.end(); ++it){

        if (*it == observer){

            observers.erase(it);        //stole algo from Iterator slides hehe
            break;
        }
    }
}

template <typename T>
void AbstractWorkItem<T>::notify() {

    for (Observer* observer : observers) {
        observer->update();
    }
}

template <typename T>
void AbstractWorkItem<T>::setState(State* newState) {

    if (state == newState) {
        return;
    }

    this->state = newState;
    notify();
}


template <typename T>
State* AbstractWorkItem<T>::getState(){

    return this->state;
}

template <typename T>
void AbstractWorkItem<T>::display(int indent = 0) {
    this->name;
}
	
template <typename T>
void AbstractWorkItem<T>::add(Component<T>* a) {
    cout << "Cannot add to AbstractWorkItem" << endl;
}

template <typename T>
void AbstractWorkItem<T>::remove(Component<T>*) {
    cout << "Cannot remove from AbstractWorkItem" << endl;
}

template <typename T>
Component<T>* AbstractWorkItem<T>::getChild(int n) {
    cout << "No children" << endl;

    return null;
}