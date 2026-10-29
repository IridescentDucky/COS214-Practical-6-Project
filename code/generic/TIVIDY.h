#ifndef TIVIDY_H
#define TIVIDY_H

#include <string>

// #include "AbstractWorkflowFactory.h"    //Abstract Fac
// #include "ConcreteWorkflowFactory1.h"   //Factory
// #include "ConcreteWorkflowFactory2.h"   //Factory
// #include "AbstractWorkflowInstanceA.h"  //AbstractProduct
// #include "AbstractWorkflowInstanceB.h"  //Abstract pRoduct

#include "AbstractWorkItem.h"
#include "WorkItem.h"

template <typename T>
class AbstractWorkItem;

template <typename T>
class WorkItem;

template <typename T>
class TIVIDY {
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
    bool addDependency(int predecessorId, int successorId);
    std::string getWorkItemState(int id) const;

    // void runWorkflow(AbstractWorkflowFactory<T>* factory);//Abtract factory

private:
    AbstractWorkItem<T>* find(int id) const;

    WorkflowMediator<T>* mediator;
    int nextId;
};

#endif
