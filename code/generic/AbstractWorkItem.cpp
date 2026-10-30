#include "AbstractWorkItem.h"
#include "State.h"

using namespace std;

template <typename T>
AbstractWorkItem<T>::AbstractWorkItem(int id, const std::string& name, WorkflowMediator<T>* mediator)
    : id(id), state(new Created<T>()), name(name), mediator(mediator), score(0), time(0)
{
}

template <typename T>
int AbstractWorkItem<T>::getId() const
{
    return this->id;
}

template <typename T>
std::string AbstractWorkItem<T>::getName() const
{
    return this->name;
}

template <typename T>
std::string AbstractWorkItem<T>::getStateName() const
{
    return this->state->getName();
}


template <typename T>
AbstractWorkItem<T>::~AbstractWorkItem(){

    delete this->state;

    //IM NOT GETTING MY PAWS DIRTY WITH THIS ONE...YET, ill wait for everyone to add their things first
    // It's easy to do - trust...
}


template <typename T>
void AbstractWorkItem<T>::attach(TaskEscalationManager<T>* observer) {

    this->observers.push_back(observer);
}

template <typename T>
void AbstractWorkItem<T>::detach(TaskEscalationManager<T>* observer) {
    for (typename std::vector<TaskEscalationManager<T>*>::iterator it = observers.begin(); it != observers.end(); ++it){
        if (*it == observer){
            this->observers.erase(it);        //stole algo from Iterator slides hehe
            break;
        }
    }
}

template <typename T>
void AbstractWorkItem<T>::notify() {
    for (TaskEscalationManager<T>* observer : observers) {
        observer->update();
    }
}

template <typename T>
void AbstractWorkItem<T>::setState(State<T>* newState) {
    if (newState == nullptr || this->state == newState) {
        return;
    }

    std::cout << "  [State] " << this->name << ": " << this->state->getName() << " -> " << newState->getName() << std::endl;
    State<T>* old = this->state;
    this->state = newState;
    delete old;
    notify();
}


template <typename T>
State<T>* AbstractWorkItem<T>::getState() const {
    return this->state;
}

template <typename T>
int AbstractWorkItem<T>::getScore() {
    return this->score;
}

template <typename T>
int AbstractWorkItem<T>::getTime() {
    return this->time;
}

template <typename T>
void AbstractWorkItem<T>::display(int indent) {
    for (int i = 0; i < indent; i++) {
        cout << "  ";
    }

    cout << this->name << " (" << this->getStateName() << ")" << endl;
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

    return nullptr;
}

template class AbstractWorkItem<int>;
