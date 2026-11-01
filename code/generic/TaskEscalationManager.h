#ifndef TaskEscalationManager_h
#define TaskEscalationManager_h

template <typename T>
class AbstractWorkItem;

/** @brief Base handler in the work-item escalation and observer chain. */
template <typename T>
class TaskEscalationManager {
protected:
    TaskEscalationManager<T>* successor = nullptr;
    T condition;
    AbstractWorkItem<T>* workItem = nullptr;   //for observer cause we need to pull the state
    
public:
    /** @brief Creates a handler with an escalation threshold.
     *  @param condition Threshold handled by this manager.
     */
    TaskEscalationManager(T condition) : condition(condition) {}
    TaskEscalationManager(const TaskEscalationManager&) = delete;
    TaskEscalationManager& operator=(const TaskEscalationManager&) = delete;

    /** @brief Handles a request or passes it to the successor.
     *  @param a Value evaluated against the handler threshold.
     */
    virtual void handleRequest(T a) = 0;
    /** @brief Sets the next handler in the escalation chain.
     *  @param next Successor handler.
     */
    void setSuccessor(TaskEscalationManager<T>* next);
    /** @brief Associates the handler with a work item.
     *  @param item Observed work item.
     */
    void setWorkItem(AbstractWorkItem<T>* item) { workItem = item; }
    /** @brief Gets the associated work item.
     *  @return Observed work item, or null if none is set.
     */
    AbstractWorkItem<T>* getWorkItem() const { return workItem; }

    /** @brief Destroys this handler and its successor chain. */
    virtual ~TaskEscalationManager();

    /** @brief Responds to a change in the associated work item. */
    virtual void update() = 0;//for observer
};

#endif
