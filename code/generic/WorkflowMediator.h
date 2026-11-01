#ifndef WORKFLOWMEDIATOR_H
#define WORKFLOWMEDIATOR_H

#include "AbstractWorkItem.h"
#include "Aggregate.h"
#include "PrototypeManager.h"

#include <vector>
#include <map>
#include <string>
#include <utility>

template <typename T>
class AbstractWorkItem;

template <typename T>
class WorkItemIterator;

template <typename T>
class Strategy;

template <typename T>
class TaskEscalationManager;

class Target;
class Adaptee;

/** @brief Coordinates work items, dependencies, strategies, and escalation. */
template <typename T>
class WorkflowMediator : public Aggregate<T> {
public:
    /** @brief Creates a mediator with default escalation levels and integrations. */
    WorkflowMediator();
    /** @brief Releases the mediator's owned handlers, work items, and integrations. */
    ~WorkflowMediator();
    WorkflowMediator(const WorkflowMediator&) = delete;
    WorkflowMediator& operator=(const WorkflowMediator&) = delete;

    /** @brief Adds a uniquely identified work item and attaches its escalation chain.
     *  @param item Work item to add; ignored if null or already registered.
     */
    void addWorkItem(AbstractWorkItem<T>* item);
    /** @brief Finds a registered work item by its ID.
     *  @param id Work-item ID to find.
     *  @return The matching work item, or null if it is not registered.
     */
    AbstractWorkItem<T>* getWorkItem(int id) const;
    /** @brief Returns the registered work items.
     *  @return The mediator's work-item collection.
     */
    const std::vector<AbstractWorkItem<T>*>& getWorkItems() const;
    /** @brief Adds a directed dependency between two registered work items.
     *  @param predecessorId ID of the work item that must complete first.
     *  @param successorId ID of the work item that depends on the predecessor.
     *  @return True if the dependency was added.
     */
    bool addDependency(int predecessorId, int successorId);

    /** @brief Processes completion notifications and starts eligible successors.
     *  @param colleague Work item whose state changed.
     */
    void notify(AbstractWorkItem<T>* colleague);

    /** @brief Replaces the work-item processing strategy.
     *  @param strategy New strategy; ownership transfers to the mediator.
     */
    void setStrategy(Strategy<T>* strategy);
    /** @brief Stores a clone of a work item as a reusable prototype.
     *  @param item Work item to clone and store.
     *  @return The prototype index, or -1 if item is null.
     */
    int savePrototype(AbstractWorkItem<T>* item);
    /** @brief Creates and registers a work item from a stored prototype.
     *  @param index Index of the prototype to clone.
     *  @param id ID to assign to the new work item.
     *  @return The registered clone, or null if the prototype or ID is invalid.
     */
    AbstractWorkItem<T>* createFromPrototype(int index, int id);
    /** @brief Replaces escalation levels and refreshes chains on existing work items.
     *  @param levels Ordered escalation names and thresholds.
     *  @return True if the levels are valid and were applied.
     */
    bool setEscalationLevels(const std::vector<std::pair<std::string, T> >& levels);
    /** @brief Returns the configured escalation levels.
     *  @return Escalation names and thresholds in order.
     */
    const std::vector<std::pair<std::string, T> >& getEscalationLevels() const;
    /** @brief Sets the name of the external system.
     *  @param name New external-system name.
     */
    void setExternalSystem(const std::string& name);
    /** @brief Returns the name of the external system.
     *  @return The external-system name.
     */
    std::string getExternalSystem() const;

    /** @brief Creates an iterator over the registered work items.
     *  @return A newly allocated work-item iterator.
     */
    Iterator<T>* createIterator() const override;
private:
    friend class WorkItemIterator<T>;

    /** @brief Builds a handler chain from the configured escalation levels.
     *  @return The first handler in the chain, or null if no levels are configured.
     */
    TaskEscalationManager<T>* createChain() const;

    std::vector<AbstractWorkItem<T>*> workItems;
    std::map<int, std::vector<int> > dependencies;
    std::vector<TaskEscalationManager<T>*> escalations;
    std::vector<std::pair<std::string, T> > levels;
    Strategy<T>* strategy;
    Adaptee* externalSystem;
    Target* external;
    PrototypeManager<T> prototypes;
};

#endif
