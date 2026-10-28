#ifndef CARETAKER_H
#define CARETAKER_H

#include "WorkItemMemento.h"
#include <vector>

class Caretaker {
private:
    std::vector<WorkItemMemento*> mementoHistory;

public:
    Caretaker() = default;
    ~Caretaker();

    void addMemento(WorkItemMemento* m);
    WorkItemMemento* getMemento(int index) const;
};

#endif
