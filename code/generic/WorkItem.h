#ifndef WORKITEM_H
#define WORKITEM_H

#include "Component.h"
#include "Subject.h"

#include <string>
#include <vector>
#include <iostream>

class Observer;
class WorkItemState;
class WorkflowMediator;
class WorkItemMemento;

//Even though im moving the entire AbstractWorkItem class, i will keep all the includes here, just in case

class WorkItem : public AbstractWorkItem, public Component, public Subject
{
public:
    WorkItem(int id, const std::string& name, int deadline, WorkflowMediator* mediator);

    void handleState() override;
    void paused() override;
    void resume() override;
    void retry() override;
    void failed() override;
    void failedDelivery() override;
    void exception() override;
    void validate() override;

    void set(const std::string& data) override;
    std::string get() const override;
    void addTimeSpent(int units) override;
    
    WorkItemMemento* createMemento() override;
    void setMemento(WorkItemMemento* m) override;

    WorkItemState* getState() const;
    void setState(WorkItemState* newState);

    bool isWithinDeadline() const;
    bool hasValidData() const;
    void notifyWorkflow();

    void operation() override;//Decorator

    void attach(Observer* observer) override;        //Observer
    void detach(Observer* observer) override;        //Observer
    void notify() override;                          //Observer

private:
    std::string data;
    int deadline;
    int timeSpent;
    std::vector<Observer*> observers; // Subject holds its observers.

};

#endif
