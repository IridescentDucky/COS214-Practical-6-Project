#include "TaskEscalationManager.h"

template <typename T>
void TaskEscalationManager<T>::setSuccessor(TaskEscalationManager* next){
    this->successor = next;
}

template <typename T>
TaskEscalationManager<T>::~TaskEscalationManager() {
    delete successor;

    successor = nullptr;
}
