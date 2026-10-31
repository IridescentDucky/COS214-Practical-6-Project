#include "TaskEscalationManager.h"
#include "AbstractWorkItem.h"

template <typename T>
void TaskEscalationManager<T>::setSuccessor(TaskEscalationManager* next){
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
