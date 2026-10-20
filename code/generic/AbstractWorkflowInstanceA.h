#ifndef ABSTRACTWORKFLOWINSTANCEA_H
#define ABSTRACTWORKFLOWINSTANCEA_H

#include <iostream>

class AbstractWorkflowInstanceA{ //Abstract Product

public:

    virtual void create() = 0;
    virtual ~AbstractWorkflowInstanceA();

};

#endif