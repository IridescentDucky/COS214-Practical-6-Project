#include "Caretaker.h"
#include <iostream>

template <typename T>
Caretaker<T>::~Caretaker() {
    for (WorkItemMemento<T>* m : mementoHistory) {
        delete m;
    }
    mementoHistory.clear();
}

template <typename T>
void Caretaker<T>::addMemento(WorkItemMemento<T>* m) {
    if (m != nullptr) {
        mementoHistory.push_back(m);
        std::cout << "[Caretaker] Saved new WorkItemMemento snapshot." << std::endl;
    }
}

template <typename T>
WorkItemMemento<T>* Caretaker<T>::getMemento(int index) const {
    if (index >= 0 && index < static_cast<int>(mementoHistory.size())) {
        std::cout << "[Caretaker] Retrieving memento snapshot at index " << index << std::endl;
        return mementoHistory[index];
    }
    std::cout << "[Caretaker] Invalid memento index requested." << std::endl;
    return nullptr;
}
