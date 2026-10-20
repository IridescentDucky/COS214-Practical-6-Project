#ifndef ABSTRACTWORKFLOWFACTORY_H
#define ABSTRACTWORKFLOWFACTORY_H

#include "AbstractWorkflowInstanceA.h"
#include "AbstractWorkflowInstanceB.h"

class AbstractWorkflowFactory{
    
public:
    virtual AbstractWorkflowInstanceA* createWorkflowInstanceA() = 0;
    virtual AbstractWorkflowInstanceB* createWorkflowInstanceB() = 0;

    virtual ~AbstractWorkflowFactory();
};

#endif