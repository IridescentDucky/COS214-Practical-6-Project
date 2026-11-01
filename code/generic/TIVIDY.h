#ifndef TIVIDY_H
#define TIVIDY_H

#include <string>
#include <utility>
#include <vector>

// #include "AbstractWorkflowFactory.h"    //Abstract Fac
// #include "ConcreteWorkflowFactory1.h"   //Factory
// #include "ConcreteWorkflowFactory2.h"   //Factory
// #include "AbstractWorkflowInstanceA.h"  //AbstractProduct
// #include "AbstractWorkflowInstanceB.h"  //Abstract pRoduct

#include "AbstractWorkItem.h"
#include "WorkItem.h"
#include "Iterator.h"
#include "Creator.h"
#include "Strategy.h"

template <typename T>
class AbstractWorkItem;

template <typename T>
class WorkItem;

/** @brief Facade for creating and managing work items and workflow operations. */
template <typename T>
class TIVIDY {
public:
    /** @brief Creates a workflow facade with its mediator and creator. */
    TIVIDY();
    /** @brief Releases the facade's owned mediator and creator. */
    ~TIVIDY();
    TIVIDY(const TIVIDY&) = delete;
    TIVIDY& operator=(const TIVIDY&) = delete;

    /** @brief Creates a work item.
     *  @param name Work-item name.
     *  @param deadline Allowed work duration.
     *  @return The new work item's ID.
     */
    int createWorkItem(const std::string& name, int deadline);
    /** @brief Advances a work item's workflow.
     *  @param id Work-item ID.
     */
    void advanceWork(int id);
    /** @brief Sets input data and advances the work item.
     *  @param id Work-item ID.
     *  @param data Data to submit.
     */
    void submitWork(int id, const std::string& data);
    /** @brief Pauses a work item. */
    void pauseWork(int id);
    /** @brief Resumes a paused work item. */
    void resumeWork(int id);
    /** @brief Records elapsed time for a work item.
     *  @param id Work-item ID.
     *  @param units Positive time units to record.
     */
    void logTime(int id, int units);
    /** @brief Adds a scored task to a work item. */
    void addTask(int id, const std::string& name, int score, int maxScore);
    /** @brief Updates a task's score.
     *  @param id Work-item ID.
     *  @param index Zero-based task index.
     *  @param score New score.
     */
    void scoreTask(int id, int index, int score);
    /** @brief Replaces the work-item scoring strategy.
     *  @param strategy Strategy to use; ownership transfers to the facade.
     */
    void setStrategy(Strategy<T>* strategy);
    /** @brief Saves a work item as a reusable template.
     *  @param id Work-item ID.
     *  @return Template index, or -1 if the item is not found.
     */
    int saveAsTemplate(int id);
    /** @brief Creates a work item from a saved template.
     *  @param templateIndex Index of the template.
     *  @param name Name for the new work item.
     *  @return The new work item's ID, or -1 if the template is invalid.
     */
    int createFromTemplate(int templateIndex, const std::string& name = "");
    /** @brief Replaces the escalation chain configuration.
     *  @param levels Ordered escalation names and thresholds.
     *  @return True if the configuration is valid and applied.
     */
    bool setEscalationLevels(const std::vector<std::pair<std::string, T> >& levels);
    /** @brief Gets the configured escalation levels. */
    const std::vector<std::pair<std::string, T> >& getEscalationLevels() const;
    /** @brief Sets the external system name.
     *  @param name New system name.
     */
    void setExternalSystem(const std::string& name);
    /** @brief Gets the external system name. */
    std::string getExternalSystem() const;
    /** @brief Prints the status of all registered work items. */
    void printStatus() const;
    /** @brief Adds a dependency between two work items.
     *  @param predecessorId ID of the work item that must finish first.
     *  @param successorId ID of the dependent work item.
     *  @return True if the dependency was added.
     */
    bool addDependency(int predecessorId, int successorId);
    /** @brief Gets a work item's current state name.
     *  @param id Work-item ID.
     *  @return State name, or an empty string if no item is found.
     */
    std::string getWorkItemState(int id) const;
    /** @brief Creates an iterator over registered work items.
     *  @return A newly allocated iterator.
     */
    Iterator<T>* createIterator() const;

    // void runWorkflow(AbstractWorkflowFactory<T>* factory);//Abtract factory

private:
    /** @brief Finds a work item by ID.
     *  @param id Work-item ID.
     *  @return The item, or null if it is not registered.
     */
    AbstractWorkItem<T>* find(int id) const;

    WorkflowMediator<T>* mediator;
    Creator<T>* creator;
    int nextId;
};

#endif
