#ifndef CONCRETEOBSERVER_H
#define CONCRETEOBSERVER_H

#include "Observer.h"

class WorkItem;

class ConcreteObserver : public Observer{

public:
    ConcreteObserver(WorkItem* item);
    void update();
    ~ConcreteObserver();

private:
    WorkItem* item; //holds the concreteSubject

};




#endif