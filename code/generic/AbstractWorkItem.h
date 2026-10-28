#ifndef ABSTRACTWORKITEM_H
#define ABSTRACTWORKITEM_H

#include "Component.h"
#include "Observer.h"

#include <vector>

class State;

class AbstractWorkItem : public Component {

private: 
    State* state;
    std::vector<Observer*> observers;

public:
    virtual ~AbstractWorkItem();

    void attach(Observer* observer);
    void detach(Observer* observer);
    void notify();

    void setState(State* newState);
    State* getState();

};

#endif 