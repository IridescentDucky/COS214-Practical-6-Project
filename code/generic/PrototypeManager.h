#ifndef PROTOTYPEMANAGER_H
#define PROTOTYPEMANAGER_H

#include "WorkItem.h"

#include <vector>
#include <iostream>

using namespace std;

class PrototypeManager {
public:
    void addPrototype(WorkItem* w);
    void removePrototype(WorkItem* w);
    WorkItem* getPrototype(int n);

    ~PrototypeManager();
private:
    vector<WorkItem*> workItems;
};

#endif