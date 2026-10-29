#ifndef WORKITEMMEMENTO_H
#define WORKITEMMEMENTO_H

#include "State.h"

// template <typename T>
// class WorkItemState;

template <typename T>
class WorkItemMemento {
private:
    State<T>* state;
    
public:
    WorkItemMemento(State<T>* s);
    ~WorkItemMemento();
    // Returns a newly allocated copy. The caller owns the returned state.
    State<T>* getState() const;
    void setState(State<T>* s);
};

#endif
