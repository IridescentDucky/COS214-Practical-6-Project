#ifndef CONCRETEWORKFLOWFACTORY1_H
#define CONCRETEWORKFLOWFACTORY1_H

#include "AbstractWorkflowFactory.h"
#include "WorkflowInstanceA1.h"
#include "WorkflowInstanceB1.h"

class ConcreteWorkflowFactory1 : public AbstractWorkflowFactory{

public:

    AbstractWorkflowInstanceA* createWorkflowInstanceA() ;

    AbstractWorkflowInstanceB* createWorkflowInstanceB();
};

#endif