// #include "Caretaker.h"
// #include "ConcreteHandler.h"
// #include "ConcreteObserver.h"
// #include "TIVIDY.h"
// #include "WorkItem.h"
// #include "WorkflowMediator.h"

#include <iostream>

int main()
{
    std::cout << "Hello world" << std::endl;
    // std::cout << "--- State, Observer, and Mediator ---" << std::endl;
    // {
    //     WorkflowMediator mediator;
    //     WorkItem* design = new WorkItem(1, "Design", 5, &mediator);
    //     WorkItem* build = new WorkItem(2, "Build", 5, &mediator);
    //     mediator.addWorkItem(design);
    //     mediator.addWorkItem(build);
    //     mediator.addDependency(design->getId(), build->getId());

    //     ConcreteObserver designObserver(design);
    //     ConcreteObserver buildObserver(build);
    //     design->handleState();
    //     design->handleState();
    //     design->set("approved design");
    //     design->handleState();
    //     design->handleState();

    //     std::cout << "--- Memento ---" << std::endl;
    //     Caretaker history;
    //     history.addMemento(build->createMemento());
    //     build->handleState();
    //     build->setMemento(history.getMemento(0));

    //     std::cout << "--- Decorator ---" << std::endl;
    //     ConcreteDecoratorA decoratedBuild(build);
    //     ConcreteDecoratorB auditedBuild(&decoratedBuild);
    //     auditedBuild.operation();
    // }

    // std::cout << "--- Abstract Factory ---" << std::endl;
    // TIVIDY tividy;
    // ConcreteWorkflowFactory1 factory1;
    // ConcreteWorkflowFactory2 factory2;
    // tividy.runWorkflow(&factory1);
    // tividy.runWorkflow(&factory2);

    // std::cout << "--- Chain of Responsibility ---" << std::endl;
    // ConcreteHandler1 firstHandler;
    // ConcreteHandler2 secondHandler;
    // firstHandler.setSuccessor(&secondHandler);
    // firstHandler.handleRequest();

    return 0;
}
