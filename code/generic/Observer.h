#ifndef OBSERVER_H
#define OBSERVER_H

#include <iostream>

class Observer{

public:

    virtual void update() = 0;
    virtual ~Observer();
};



#endif