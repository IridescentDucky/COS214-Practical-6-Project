#ifndef WORKITEMMEMENTO_H
#define WORKITEMMEMENTO_H

#include "State.h"

// template <typename T>
// class WorkItemState;

/** @brief Snapshot holding a work item's workflow state. */
template <typename T>
class WorkItemMemento {
private:
    State<T>* state;
    
public:
    /** @brief Saves a copy of the supplied state.
     *  @param s State to capture.
     */
    WorkItemMemento(State<T>* s);
    /** @brief Releases the saved state. */
    ~WorkItemMemento();
    WorkItemMemento(const WorkItemMemento&) = delete;
    WorkItemMemento& operator=(const WorkItemMemento&) = delete;
    // Returns a newly allocated copy. The caller owns the returned state.
    /** @brief Gets a newly allocated copy of the saved state.
     *  @return State copy owned by the caller.
     */
    State<T>* getState() const;
    /** @brief Replaces the saved state.
     *  @param s State to save.
     */
    void setState(State<T>* s);
};

#endif
