#ifndef CONCRETEOBSERVER_H
#define CONCRETEOBSERVER_H

#include "Observer.h"

class AbstractWorkItem;
class Handler;

class ConcreteObserver : public Observer{

public:
    ConcreteObserver(AbstractWorkItem* subject, Handler* handler);
    void update();
    ~ConcreteObserver();

private:
    AbstractWorkItem* subject;
    Handler* handler;

};




#endif
