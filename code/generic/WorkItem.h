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

/** @brief Concrete work item with state, task, data, and time tracking. */
template <typename T>
class WorkItem : public AbstractWorkItem<T> {
    
private:
    int deadline;
    int timeSpent;
    std::string data;
    std::vector<TaskRecord> tasks;
    //std::vector<Observer*> observers; // Subject holds its observers.
    
public:
    /** @brief Creates a work item with its deadline and workflow mediator.
     *  @param id Work-item identifier.
     *  @param name Work-item name.
     *  @param deadline Allowed work duration.
     *  @param mediator Mediator coordinating workflow events.
     */
    WorkItem(int id, const std::string& name, int deadline, WorkflowMediator<T>* mediator);

    /** @brief Advances the item's current workflow state. */
    void handleState() override;
    /** @brief Pauses the item. */
    void paused() override;
    /** @brief Resumes the item. */
    void resume() override;
    /** @brief Retries the item. */
    void retry() override;
    /** @brief Marks the item failed. */
    void failed() override;
    /** @brief Handles delivery failure. */
    void failedDelivery() override;
    /** @brief Handles an exception. */
    void exception() override;
    /** @brief Validates the item. */
    void validate() override;

    /** @brief Sets the item's input data.
     *  @param data New input data.
     */
    void set(const std::string& data) override;
    /** @brief Gets the item's input data. */
    std::string get() const override;
    /** @brief Adds elapsed time to the item.
     *  @param units Time units to add.
     */
    void addTimeSpent(int units) override;
    /** @brief Gets time spent beyond the deadline. */
    int getOverdue() const override;
    /** @brief Gets the total task score. */
    int getScore() override;
    /** @brief Gets the deadline allowance. */
    int getTime() override;
    /** @brief Clones this item with the requested ID and mediator. */
    AbstractWorkItem<T>* clone(int id, WorkflowMediator<T>* mediator) const override;
    
    /** @brief Captures this item's state in a memento. */
    WorkItemMemento<T>* createMemento() override;
    /** @brief Restores this item's state from a memento. */
    void setMemento(WorkItemMemento<T>* m) override;

    /** @brief Gets the current state object. */
    State<T>* getState() const;
    //void setState(State<T>* newState);   //this needs to be handled by AbstractWorkItem, since thats the context

    /** @brief Checks whether the deadline has not been exceeded. */
    bool isWithinDeadline() const;
    /** @brief Checks whether the submitted data is valid. */
    bool hasValidData() const;
    /** @brief Notifies the mediator about a workflow change. */
    void notifyWorkflow();

    // void attach(Observer* observer) override;        //Observer
    // void detach(Observer* observer) override;        //Observer
    // void notify() override;                          //Observer

    /** @brief Adds a task with its score and maximum score. */
    void addTask(const std::string& name, int score, int maxScore) override;
    /** @brief Calculates the average task score. */
    double getAverageScore() const override;
    /** @brief Gets a task by its zero-based index. */
    const TaskRecord& getTask(int index) const override;
    /** @brief Gets the number of tasks. */
    int getTaskCount() const override;
    /** @brief Changes a task's score.
     *  @param index Zero-based task index.
     *  @param newScore Replacement score.
     */
    void updateTaskScore(int index, int newScore) override;
    
};

#endif
