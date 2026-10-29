#ifndef ABSTRACTWORKITEM_H
#define ABSTRACTWORKITEM_H

#include "Component.h"
#include "Observer.h"

#include <string>
#include <vector>
#include <iostream>

class Observer;
class State;
class WorkflowMediator;
class WorkItemMemento;

class AbstractWorkItem : public Component {

protected: 
    State* state;
    std::vector<Observer*> observers;
    int id;
    std::string name;
    WorkflowMediator* mediator;
    
public:

    AbstractWorkItem(int id, const std::string& name, WorkflowMediator* mediator);
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
    
    virtual WorkItemMemento* createMemento() = 0;   //MEMENTO
    virtual void setMemento(WorkItemMemento* m) = 0;

    void attach(Observer* observer);    //FOR OBSERVER
    void detach(Observer* observer);    ///OBSERVER
    void notify();            //OBSERVER

    void setState(State* newState);
    State* getState();

};

#endif 
