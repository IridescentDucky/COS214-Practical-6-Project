#ifndef ABSTRACTWORKITEM_H
#define ABSTRACTWORKITEM_H

#include "WorkflowMediator.h"
#include "WorkItemMemento.h"
#include "Component.h"
#include "Observer.h"
#include "State.h"

#include <string>
#include <vector>
#include <iostream>

class Observer;

// template <typename T>
// class State;

// template <typename T>
// class WorkflowMediator;

// template <typename T>
// class WorkItemMemento;

template <typename T>
class AbstractWorkItem : public Component<T> {
protected: 
    int id;
    State<T>* state;
    std::string name;
    std::vector<Observer*> observers;
    WorkflowMediator<T>* mediator;
    
public:
    AbstractWorkItem(int id, const std::string& name, WorkflowMediator<T>* mediator);
    virtual ~AbstractWorkItem();

    int getId() const;
    std::string getName() const;
    std::string getStateName() const;

    virtual void handleState() = 0; //STATE FUNCTIONS
    virtual void paused() = 0;
    virtual void resume() = 0;
    virtual void retry() = 0;
    virtual void failed() = 0;
    virtual void failedDelivery() = 0;
    virtual void exception() = 0;
    virtual void validate() = 0;

    virtual void set(const std::string& data) = 0;  //?
    virtual std::string get() const = 0;
    virtual void addTimeSpent(int units) = 0;
    
    virtual WorkItemMemento<T>* createMemento() = 0;   //MEMENTO
    virtual void setMemento(WorkItemMemento<T>* m) = 0;

    void attach(Observer* observer);    //FOR OBSERVER
    void detach(Observer* observer);    ///OBSERVER
    void notify();            //OBSERVER

    void setState(State<T>* newState);
    State<T>* getState();

    // Composite
    void display(int indent = 0); 
	void add(Component<T>*);
    void remove(Component<T>*);
    Component<T>* getChild(int n);
};

#endif 
