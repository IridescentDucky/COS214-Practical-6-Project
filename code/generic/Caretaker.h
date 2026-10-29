#ifndef CARETAKER_H
#define CARETAKER_H

#include "WorkItemMemento.h"
#include <vector>

template <typename T>
class Caretaker {
private:
    std::vector<WorkItemMemento<T>*> mementoHistory;

public:
    Caretaker() = default;
    ~Caretaker();

    void addMemento(WorkItemMemento<T>* m);
    WorkItemMemento<T>* getMemento(int index) const;
};

#endif
