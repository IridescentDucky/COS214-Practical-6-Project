#include "ConcreteWorkflowFactory1.h"


AbstractWorkflowInstanceA* ConcreteWorkflowFactory1::createWorkflowInstanceA(){

    return new WorkflowInstanceA1();
}

AbstractWorkflowInstanceB* ConcreteWorkflowFactory1::createWorkflowInstanceB(){
    
    return new WorkflowInstanceB1();
}