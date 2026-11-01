#ifndef CARETAKER_H
#define CARETAKER_H

#include "WorkItemMemento.h"
#include <vector>

/** @brief Stores and retrieves snapshots of a work item's state. */
template <typename T>
class Caretaker {
private:
    std::vector<WorkItemMemento<T>*> mementoHistory;

public:
    /** @brief Creates an empty snapshot history. */
    Caretaker() = default;
    /** @brief Releases all snapshots owned by this caretaker. */
    ~Caretaker();
    Caretaker(const Caretaker&) = delete;
    Caretaker& operator=(const Caretaker&) = delete;

    /** @brief Adds a snapshot to the history.
     *  @param m Snapshot to store.
     */
    void addMemento(WorkItemMemento<T>* m);
    /** @brief Gets a snapshot by its position in the history.
     *  @param index Zero-based snapshot index.
     *  @return The snapshot, or null if the index is invalid.
     */
    WorkItemMemento<T>* getMemento(int index) const;
};

#endif
