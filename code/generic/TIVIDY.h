#ifndef TIVIDY_H
#define TIVIDY_H

#include <string>

#include "AbstractWorkflowFactory.h"    //Abstract Fac
#include "ConcreteWorkflowFactory1.h"   //Factory
#include "ConcreteWorkflowFactory2.h"   //Factory
#include "AbstractWorkflowInstanceA.h"  //AbstractProduct
#include "AbstractWorkflowInstanceB.h"  //Abstract pRoduct

class AbstractWorkItem;
class WorkflowMediator;

class TIVIDY
{
public:
    TIVIDY();
    ~TIVIDY();
    TIVIDY(const TIVIDY&) = delete;
    TIVIDY& operator=(const TIVIDY&) = delete;

    int createWorkItem(const std::string& name, int deadline);
    void advanceWork(int id);
    void submitWork(int id, const std::string& data);
    void pauseWork(int id);
    void resumeWork(int id);
    void printStatus() const;

    void runWorkflow(AbstractWorkflowFactory* factory);//Abtract factory

private:
    AbstractWorkItem* find(int id) const;

    WorkflowMediator* mediator;
    int nextId;
};

#endif
