#include "Caretaker.h"
#include <iostream>

Caretaker::~Caretaker() {
    for (WorkItemMemento* m : mementoHistory) {
        delete m;
    }
    mementoHistory.clear();
}

void Caretaker::addMemento(WorkItemMemento* m) {
    if (m != nullptr) {
        mementoHistory.push_back(m);
        std::cout << "[Caretaker] Saved new WorkItemMemento snapshot." << std::endl;
    }
}

WorkItemMemento* Caretaker::getMemento(int index) const {
    if (index >= 0 && index < static_cast<int>(mementoHistory.size())) {
        std::cout << "[Caretaker] Retrieving memento snapshot at index " << index << std::endl;
        return mementoHistory[index];
    }
    std::cout << "[Caretaker] Invalid memento index requested." << std::endl;
    return nullptr;
}
