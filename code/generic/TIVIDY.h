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
#include "Iterator.h"
#include "Creator.h"
#include "Strategy.h"

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
    void logTime(int id, int units);
    void addTask(int id, const std::string& name, int score, int maxScore);
    void setStrategy(Strategy<T>* strategy);
    int saveAsTemplate(int id);
    int createFromTemplate(int templateIndex);
    void printStatus() const;
    bool addDependency(int predecessorId, int successorId);
    std::string getWorkItemState(int id) const;
    Iterator<T>* createIterator() const;

    // void runWorkflow(AbstractWorkflowFactory<T>* factory);//Abtract factory

private:
    AbstractWorkItem<T>* find(int id) const;

    WorkflowMediator<T>* mediator;
    Creator<T>* creator;
    int nextId;
};

#endif
