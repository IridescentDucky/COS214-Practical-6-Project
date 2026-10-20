#ifndef ABSTRACTWORKFLOWINSTANCEB_H
#define ABSTRACTWORKFLOWINSTANCEB_H

#include <iostream>

class AbstractWorkflowInstanceB{
//Abstract Product
public:
    virtual void create() = 0;
    virtual ~AbstractWorkflowInstanceB();

};

#endif