#ifndef STATSCARETAKER_H
#define STATSCARETAKER_H

class StatsMemento;

/** @brief Stores a statistics snapshot for later restoration. */
class StatsCaretaker{
    
private:
    StatsMemento* memento;

public:
    /** @brief Creates a caretaker with no saved snapshot. */
    StatsCaretaker();
    /** @brief Releases the saved snapshot. */
    ~StatsCaretaker();
    StatsCaretaker(const StatsCaretaker&) = delete;
    StatsCaretaker& operator=(const StatsCaretaker&) = delete;

    /** @brief Gets the currently saved snapshot.
     *  @return The saved snapshot, or null if none is stored.
     */
    StatsMemento* getMemento() const;
    /** @brief Saves a statistics snapshot.
     *  @param m Snapshot to store.
     */
    void saveMemento(StatsMemento* m);
};

#endif
