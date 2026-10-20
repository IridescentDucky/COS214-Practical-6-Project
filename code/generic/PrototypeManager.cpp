#include "PrototypeManager.h"

void PrototypeManager::addPrototype(WorkItem* w) {
    if (w != nullptr) {
        workItems.push_back(w);
    }
}

void PrototypeManager::removePrototype(WorkItem* w) {
    for (vector<WorkItem*>::iterator it = workItems.begin(); it != workItems.end(); ++it) {
        if (*it == w) {
            workItems.erase(it);
            break;
        }
    }
}

PrototypeManager::~PrototypeManager() {
    for (WorkItem* w : workItems) {
        delete w;
    }

    workItems.clear();    
}