#ifndef WORKITEM_H
#define WORKITEM_H

#include "Component.h"
#include "AbstractWorkItem.h"
// #include "Subject.h"

#include <string>
#include <vector>
#include <iostream>

// class Observer;
// class WorkItemState;
// class WorkflowMediator;
// class WorkItemMemento;

template <typename T>
class WorkItem : public AbstractWorkItem<T> {
public:
    WorkItem(int id, const std::string& name, int deadline, WorkflowMediator<T>* mediator);

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
    
    WorkItemMemento<T>* createMemento() override;
    void setMemento(WorkItemMemento<T>* m) override;

    State<T>* getState() const;
    void setState(State<T>* newState);

    bool isWithinDeadline() const;
    bool hasValidData() const;
    void notifyWorkflow();

    void attach(Observer* observer) override;        //Observer
    void detach(Observer* observer) override;        //Observer
    void notify() override;                          //Observer
private:
    int deadline;
    int timeSpent;
    std::string data;
    std::vector<Observer*> observers; // Subject holds its observers.

};

#endif
