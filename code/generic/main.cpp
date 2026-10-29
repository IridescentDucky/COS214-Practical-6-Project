#include "Caretaker.h"
#include "ConcreteDecoratorA.h"
#include "ConcreteDecoratorB.h"
#include "ConcreteHandler1.h"
#include "ConcreteHandler2.h"
#include "ConcreteObserver.h"
#include "ConcreteStrategyA.h"
#include "ConcreteWorkflowFactory1.h"
#include "ConcreteWorkflowFactory2.h"
#include "TIVIDY.h"
#include "WorkItem.h"
#include "WorkflowMediator.h"

#include <iostream>

int main()
{
    std::cout << "--- State, Observer, and Mediator ---" << std::endl;
    {
        WorkflowMediator mediator;
        WorkItem* design = new WorkItem(1, "Design", 5, &mediator);
        WorkItem* build = new WorkItem(2, "Build", 5, &mediator);
        mediator.addWorkItem(design);
        mediator.addWorkItem(build);
        mediator.addDependency(design->getId(), build->getId());

        ConcreteObserver designObserver(design);
        ConcreteObserver buildObserver(build);
        design->handleState();
        design->handleState();
        design->set("approved design");
        design->handleState();
        design->handleState();

        std::cout << "--- Memento ---" << std::endl;
        Caretaker history;
        history.addMemento(build->createMemento());
        build->handleState();
        build->setMemento(history.getMemento(0));

        std::cout << "--- Decorator ---" << std::endl;
        ConcreteDecoratorA decoratedBuild(build);
        ConcreteDecoratorB auditedBuild(&decoratedBuild);
        auditedBuild.operation();
    }

    std::cout << "--- Abstract Factory ---" << std::endl;
    TIVIDY tividy;
    ConcreteWorkflowFactory1 factory1;
    ConcreteWorkflowFactory2 factory2;
    tividy.runWorkflow(&factory1);
    tividy.runWorkflow(&factory2);
    
    std::cout << "--- Strategy ---" << std::endl;
    ConcreteStrategyA strategy;
    strategy.algorithm();

    std::cout << "--- Iterator ---" << std::endl;
    tividy.createWorkItem("Plan", 5);
    tividy.createWorkItem("Review", 5);
    Iterator* it = tividy.createIterator();
    while (it->hasNext())
    {
        AbstractWorkItem* item = it->next();
        std::cout << "  " << item->getId() << " " << item->getName() << ": " << item->getStateName() << std::endl;
    }
    delete it;

    std::cout << "--- Chain of Responsibility ---" << std::endl;
    ConcreteHandler1 firstHandler;
    ConcreteHandler2 secondHandler;
    firstHandler.setSuccessor(&secondHandler);
    firstHandler.handleRequest();

    return 0;
}
