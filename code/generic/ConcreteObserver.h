#ifndef CONCRETEOBSERVER_H
#define CONCRETEOBSERVER_H

#include "Observer.h"
#include "AbstractWorkItem.h"
#include "TaskEscalationManager.h"

// class AbstractWorkItem;
// class Handler;

template <typename T>
class ConcreteObserver : public Observer {
public:
    ConcreteObserver(AbstractWorkItem<T>* subject, TaskEscalationManager<T>* handler);
    void update();
    ~ConcreteObserver();

private:
    AbstractWorkItem<T>* subject;
    TaskEscalationManager<T>* handler;
};




#endif
