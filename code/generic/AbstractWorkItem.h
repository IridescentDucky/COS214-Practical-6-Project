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


/** @brief Score and maximum score for a named task within a work item. */
struct TaskRecord {
    std::string name;
    int score;
    int maxScore;

    /** @brief Creates an empty task record. */
    TaskRecord() : name(""), score(0), maxScore(0) {}
    /** @brief Creates a task record with the supplied score values.
     *  @param n Task name.
     *  @param s Current task score.
     *  @param ms Maximum task score.
     */
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

/** @brief Common interface and state for workflow work items. */
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
    /** @brief Initializes a work item and its workflow context.
     *  @param id Work-item identifier.
     *  @param name Work-item name.
     *  @param mediator Mediator coordinating workflow events.
     */
    AbstractWorkItem(int id, const std::string& name, WorkflowMediator<T>* mediator);
    /** @brief Destroys the work item and its owned state. */
    virtual ~AbstractWorkItem();
    AbstractWorkItem(const AbstractWorkItem&) = delete;
    AbstractWorkItem& operator=(const AbstractWorkItem&) = delete;

    /** @brief Gets the work-item identifier. */
    int getId() const;
    /** @brief Gets the work-item name. */
    std::string getName() const;
    /** @brief Changes the work-item name.
     *  @param name New name.
     */
    void rename(const std::string& name);
    /** @brief Gets the current workflow state name. */
    std::string getStateName() const;

    /** @brief Advances the work item's workflow state. */
    virtual void handleState() = 0; //STATE FUNCTIONS
    /** @brief Pauses the work item. */
    virtual void paused() = 0;
    /** @brief Resumes the work item. */
    virtual void resume() = 0;
    /** @brief Retries the work item. */
    virtual void retry() = 0;
    /** @brief Marks the work item as failed. */
    virtual void failed() = 0;
    /** @brief Handles work-item delivery failure. */
    virtual void failedDelivery() = 0;
    /** @brief Handles a work-item exception. */
    virtual void exception() = 0;
    /** @brief Validates the work item. */
    virtual void validate() = 0;

    /** @brief Sets the work item's input data.
     *  @param data New data.
     */
    virtual void set(const std::string& data) = 0;  //?
    /** @brief Gets the work item's input data. */
    virtual std::string get() const = 0;
    /** @brief Adds elapsed time to the work item.
     *  @param units Number of time units to add.
     */
    virtual void addTimeSpent(int units) = 0;
    /** @brief Gets the work item's overdue time. */
    virtual int getOverdue() const = 0;
    /** @brief Clones the work item with a new identity and mediator.
     *  @param id Identifier for the clone.
     *  @param mediator Mediator for the clone.
     *  @return A newly allocated work-item clone.
     */
    virtual AbstractWorkItem<T>* clone(int id, WorkflowMediator<T>* mediator) const = 0;
    
    /** @brief Captures the work item's current state.
     *  @return A newly allocated memento.
     */
    virtual WorkItemMemento<T>* createMemento() = 0;   //MEMENTO
    /** @brief Restores work-item state from a memento.
     *  @param m Memento to restore.
     */
    virtual void setMemento(WorkItemMemento<T>* m) = 0;

    /** @brief Subscribes an escalation handler to this work item.
     *  @param observer Handler to attach.
     */
    virtual void attach(TaskEscalationManager<T>* observer);    //FOR OBSERVER
    /** @brief Removes an escalation handler from this work item.
     *  @param observer Handler to detach.
     */
    virtual void detach(TaskEscalationManager<T>* observer);    ///OBSERVER
    /** @brief Notifies attached handlers of a work-item change. */
    virtual void notify();            //OBSERVER

    /** @brief Changes the current workflow state.
     *  @param newState State to adopt.
     */
    virtual void setState(State<T>* newState);
    /** @brief Gets the current workflow state. */
    State<T>* getState() const;

    /** @brief Gets the work item's score. */
    int getScore();
    /** @brief Gets the work item's time allowance. */
    int getTime();

    // Composite
    /** @brief Displays the work item.
     *  @param indent Indentation level used for hierarchical output.
     */
    void display(int indent = 0); 
    /** @brief Adds a child component when supported. */
	void add(Component<T>*);
    /** @brief Removes a child component when supported. */
    void remove(Component<T>*);
    /** @brief Gets a child component when supported.
     *  @param n Zero-based child index.
     */
    Component<T>* getChild(int n);
    
    // For task vector
    /** @brief Adds a scored task to the work item. */
    virtual void addTask(const std::string& name, int score, int maxScore) = 0;
    /** @brief Calculates the average score of the work item's tasks. */
    virtual double getAverageScore() const = 0;
    /** @brief Gets a task by index.
     *  @param index Zero-based task index.
     *  @return The selected task record.
     */
    virtual const TaskRecord& getTask(int index) const = 0;
    /** @brief Gets the number of tasks. */
    virtual int getTaskCount() const = 0;
    /** @brief Updates the score of a task.
     *  @param index Zero-based task index.
     *  @param newScore Replacement score.
     */
    virtual void updateTaskScore(int index, int newScore) = 0;
};

#endif 
