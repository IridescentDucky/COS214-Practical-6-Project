#ifndef STATE_H
#define STATE_H

#include <string>

template <typename T>
class WorkItem;

/** @brief Base state defining valid workflow transitions. */
template <typename T>
class State {
public:
    /** @brief Destroys the state through its base interface. */
    virtual ~State() {}
    
    /** @brief Gets the state's display name.
     *  @return State name.
     */
    virtual std::string getName() const = 0;
    /** @brief Creates an independent copy of the state.
     *  @return A newly allocated state copy.
     */
    virtual State<T>* clone() const = 0;

    /** @brief Advances the work item to its next state. */
    virtual void nextState(WorkItem<T>* item);
    /** @brief Pauses the work item when allowed in this state. */
    virtual void paused(WorkItem<T>* item);
    /** @brief Resumes the work item when allowed in this state. */
    virtual void resume(WorkItem<T>* item);
    /** @brief Retries the work item when allowed in this state. */
    virtual void retry(WorkItem<T>* item);
    /** @brief Marks the work item failed when allowed in this state. */
    virtual void failed(WorkItem<T>* item);
    /** @brief Handles failed delivery when allowed in this state. */
    virtual void failedDelivery(WorkItem<T>* item);
    /** @brief Handles an exception when allowed in this state. */
    virtual void exception(WorkItem<T>* item);
    /** @brief Validates the work item when allowed in this state. */
    virtual void validate(WorkItem<T>* item);

protected:
    /** @brief Reports a workflow operation that is invalid for this state.
     *  @param operation Name of the rejected operation.
     */
    void reject(const std::string& operation) const;
};

/** @brief State before a work item has been delivered. */
template <typename T>
class Created : public State<T>
{
public:
    /** @brief Gets the state name. */
    std::string getName() const override;
    /** @brief Clones this state. */
    State<T>* clone() const override;
    /** @brief Delivers the work item. */
    void nextState(WorkItem<T>* item) override;
};

/** @brief State after a work item has been delivered. */
template <typename T>
class Delivered : public State<T>
{
public:
    /** @brief Gets the state name. */
    std::string getName() const override;
    /** @brief Clones this state. */
    State<T>* clone() const override;
    /** @brief Starts work on the delivered item. */
    void nextState(WorkItem<T>* item) override;
    /** @brief Handles a delivery failure. */
    void failedDelivery(WorkItem<T>* item) override;
    /** @brief Retries a delivered item. */
    void retry(WorkItem<T>* item) override;
};

/** @brief State while a work item is being processed. */
template <typename T>
class InProgress : public State<T>
{
public:
    /** @brief Gets the state name. */
    std::string getName() const override;
    /** @brief Clones this state. */
    State<T>* clone() const override;
    /** @brief Advances processing to validation. */
    void nextState(WorkItem<T>* item) override;
    /** @brief Pauses active work. */
    void paused(WorkItem<T>* item) override;
    /** @brief Marks active work as failed. */
    void failed(WorkItem<T>* item) override;
    /** @brief Moves active work to the exception state. */
    void exception(WorkItem<T>* item) override;
};

/** @brief State while a work item is paused. */
template <typename T>
class Paused : public State<T>
{
public:
    /** @brief Gets the state name. */
    std::string getName() const override;
    /** @brief Clones this state. */
    State<T>* clone() const override;
    /** @brief Advances the paused item when requested. */
    void nextState(WorkItem<T>* item) override;
    /** @brief Resumes paused work. */
    void resume(WorkItem<T>* item) override;
};

/** @brief Terminal state for successfully completed work. */
template <typename T>
class Completed : public State<T>
{
public:
    /** @brief Gets the state name. */
    std::string getName() const override;
    /** @brief Clones this state. */
    State<T>* clone() const override;
    /** @brief Handles an attempted transition from completion. */
    void nextState(WorkItem<T>* item) override;
};

/** @brief State where completed work is validated. */
template <typename T>
class Validation : public State<T>
{
public:
    /** @brief Gets the state name. */
    std::string getName() const override;
    /** @brief Clones this state. */
    State<T>* clone() const override;
    /** @brief Completes the item after validation. */
    void nextState(WorkItem<T>* item) override;
    /** @brief Retries work after unsuccessful validation. */
    void retry(WorkItem<T>* item) override;
    /** @brief Marks the item failed after validation. */
    void failed(WorkItem<T>* item) override;
};

/** @brief Terminal state for work that has failed. */
template <typename T>
class Failed : public State<T>
{
public:
    /** @brief Gets the state name. */
    std::string getName() const override;
    /** @brief Clones this state. */
    State<T>* clone() const override;
    /** @brief Handles an attempted transition from failure. */
    void nextState(WorkItem<T>* item) override;
};

/** @brief Terminal state for archived work. */
template <typename T>
class Archived : public State<T>
{
public:
    /** @brief Gets the state name. */
    std::string getName() const override;
    /** @brief Clones this state. */
    State<T>* clone() const override;
    /** @brief Handles an attempted transition from archive. */
    void nextState(WorkItem<T>* item) override;
};

/** @brief State for work that encountered an exception. */
template <typename T>
class Exception : public State<T>
{
public:
    /** @brief Gets the state name. */
    std::string getName() const override;
    /** @brief Clones this state. */
    State<T>* clone() const override;
    /** @brief Handles an attempted transition from the exception state. */
    void nextState(WorkItem<T>* item) override;
    /** @brief Validates work after exception handling. */
    void validate(WorkItem<T>* item) override;
};

#endif
