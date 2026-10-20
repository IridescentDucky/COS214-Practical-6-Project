#include "ConcreteWorkflowFactory2.h"

AbstractWorkflowInstanceA* ConcreteWorkflowFactory2::createWorkflowInstanceA(){

    return new WorkflowInstanceA2();
}

AbstractWorkflowInstanceB* ConcreteWorkflowFactory2::createWorkflowInstanceB(){

    return new WorkflowInstanceB2();

}