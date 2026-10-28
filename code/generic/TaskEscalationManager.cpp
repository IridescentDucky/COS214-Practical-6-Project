#include "TaskEscalationManager.h"

void TaskEscalationManager::setSuccessor(TaskEscalationManager* next){
    this->successor = next;
}

TaskEscalationManager::~TaskEscalationManager() {
    delete successor;

    successor = nullptr;
}
