#include "TaskEscalationManager.h"
#include "AbstractWorkItem.h"

#include <iostream>

template <typename T>
void TaskEscalationManager<T>::setSuccessor(TaskEscalationManager* next){
    for (TaskEscalationManager<T>* link = next; link != nullptr; link = link->successor) {
        if (link == this) {
            std::cout << "[TaskEscalationManager] Rejected successor: it would make the chain loop." << std::endl;
            return;
        }
    }

    TaskEscalationManager<T>* old = this->successor;
    if (old != nullptr && old != next) {
        for (TaskEscalationManager<T>* link = old; link != nullptr; link = link->successor) {
            if (link->successor == next) {
                link->successor = nullptr;
                break;
            }
        }
        delete old;
    }
    this->successor = next;
}

template <typename T>
TaskEscalationManager<T>::~TaskEscalationManager() {
    if (workItem != nullptr) {
        workItem->detach(this);
    }

    delete successor;

    successor = nullptr;
}

template class TaskEscalationManager<int>;
