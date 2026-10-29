#ifndef CONCRETEWORKFLOWFACTORY2_H
#define CONCRETEWORKFLOWFACTORY2_H

#include "AbstractWorkflowFactory.h"
#include "WorkflowInstanceA2.h"
#include "WorkflowInstanceB2.h"

class ConcreteWorkflowFactory2 : public AbstractWorkflowFactory{

public:
    AbstractWorkflowInstanceA* createWorkflowInstanceA();
    AbstractWorkflowInstanceB* createWorkflowInstanceB();

};

#endif