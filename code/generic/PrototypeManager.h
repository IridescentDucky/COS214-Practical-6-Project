#ifndef PROTOTYPEMANAGER_H
#define PROTOTYPEMANAGER_H

#include "AbstractWorkItem.h"

// template <typename T>
// class AbstractWorkItem;

template <typename T>
class PrototypeManager {
private: 
    AbstractWorkItem<T>** workitems;
    int size, capacity;

    void resize(int);
public:
    PrototypeManager(int = 10);

    void addPrototype(AbstractWorkItem<T>*);
    void removePrototype(AbstractWorkItem<T>*);

    AbstractWorkItem<T>* getPrototype(int);

    ~PrototypeManager();
};

#endif
