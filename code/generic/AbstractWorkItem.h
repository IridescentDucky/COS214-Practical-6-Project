#ifndef ABSTRACTWORKITEM_H
#define ABSTRACTWORKITEM_H

#include "WorkflowMediator.h"
#include "WorkItemMemento.h"
#include "Component.h"
#include "TaskEscalationManager.h"
#include "State.h"

#include <string>
#include <vector>
#include <iostream>


// Struct for the vector so that it can be used across our scenarios

struct TaskRecord {
    std::string name;
    int score;
    int maxScore;

    TaskRecord() : name(""), score(0), maxScore(0) {}
    TaskRecord(const std::string& n, int s, int ms) : name(n), score(s), maxScore(ms) {}
};

// template <typename T>
// class State;

template <typename T>
class WorkflowMediator;

template <typename T>
class TaskEscalationManager;

// template <typename T>
// class WorkItemMemento;

template <typename T>
class AbstractWorkItem : public Component<T> {
protected: 
    int id;
    State<T>* state;
    std::string name;
    WorkflowMediator<T>* mediator;
    std::vector<TaskEscalationManager<T>*> observers;
    int score;
    int time;
    
public:
    AbstractWorkItem(int id, const std::string& name, WorkflowMediator<T>* mediator);
    virtual ~AbstractWorkItem();
    AbstractWorkItem(const AbstractWorkItem&) = delete;
    AbstractWorkItem& operator=(const AbstractWorkItem&) = delete;

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
    virtual int getOverdue() const = 0;
    virtual AbstractWorkItem<T>* clone(int id, WorkflowMediator<T>* mediator) const = 0;
    
    virtual WorkItemMemento<T>* createMemento() = 0;   //MEMENTO
    virtual void setMemento(WorkItemMemento<T>* m) = 0;

    virtual void attach(TaskEscalationManager<T>* observer);    //FOR OBSERVER
    virtual void detach(TaskEscalationManager<T>* observer);    ///OBSERVER
    virtual void notify();            //OBSERVER

    virtual void setState(State<T>* newState);
    State<T>* getState() const;

    int getScore();
    int getTime();

    // Composite
    void display(int indent = 0); 
	void add(Component<T>*);
    void remove(Component<T>*);
    Component<T>* getChild(int n);
    
    // For task vector
    virtual void addTask(const std::string& name, int score, int maxScore) = 0;
    virtual double getAverageScore() const = 0;
    virtual const TaskRecord& getTask(int index) const = 0;
    virtual int getTaskCount() const = 0;
    virtual void updateTaskScore(int index, int newScore) = 0;
};

#endif 
