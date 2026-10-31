#include "Adaptee.h"
#include "Adapter.h"
#include "BonusScoreDecorator.h"
#include "BonusTimeDecorator.h"
#include "Caretaker.h"
#include "Composite.h"
#include "ConcreteCreator.h"
#include "ConcreteHandler.h"
#include "ConcreteStrategyA.h"
#include "ConcreteStrategyB.h"
#include "ConcreteStrategyC.h"
#include "Iterator.h"
#include "TIVIDY.h"
#include "WorkItem.h"
#include "PrototypeManager.h"

#include <iostream>

int main()
{
    std::cout << "=== 1. Facade + State ===" << std::endl;
    TIVIDY<int> tividy;
    int design = tividy.createWorkItem("Design", 5);
    int build = tividy.createWorkItem("Build", 5);
    int test = tividy.createWorkItem("Test", 5);
    tividy.pauseWork(design);
    tividy.advanceWork(design);
    tividy.advanceWork(design);
    tividy.pauseWork(design);
    tividy.resumeWork(design);

    std::cout << std::endl << "=== 2. Mediator ===" << std::endl;
    tividy.addDependency(design, build);
    tividy.addDependency(design, test);
    tividy.submitWork(design, "approved design");
    tividy.advanceWork(design);

    std::cout << std::endl << "=== 3. Iterator ===" << std::endl;
    Iterator<int>* it = tividy.createIterator();
    while (it->hasNext())
    {
        AbstractWorkItem<int>* item = it->next();
        std::cout << "  " << item->getId() << " " << item->getName() << ": " << item->getStateName() << std::endl;
    }
    delete it;

    std::cout << std::endl << "=== 4. Observer ===" << std::endl;
    WorkItem<int> review(10, "Review", 5, nullptr);
    {
        ConcreteHandler<int> watcher("Review watcher", 1);
        review.attach(&watcher);
        review.handleState();
        review.handleState();
        review.detach(&watcher);
    }

    std::cout << std::endl << "=== 5. Memento ===" << std::endl;
    Caretaker<int> history;
    history.addMemento(review.createMemento());
    review.exception();
    review.setMemento(history.getMemento(0));
    std::cout << "  Review is back in " << review.getStateName() << std::endl;

    std::cout << std::endl << "=== 6. Decorator ===" << std::endl;
    BonusScoreDecorator<int> scored(&review, 10, 2);
    BonusTimeDecorator<int> extended(&scored, 3);
    extended.display();
    std::cout << "  Score: " << extended.getScore() << ", extra time: " << extended.getTime() << std::endl;

    std::cout << std::endl << "=== 7. Composite ===" << std::endl;
    Composite<int>* sprint = new Composite<int>("Sprint 1");
    sprint->add(new WorkItem<int>(20, "Write spec", 5, nullptr));
    sprint->add(new WorkItem<int>(21, "Build prototype", 5, nullptr));
    sprint->display();
    delete sprint;

    std::cout << std::endl << "=== 8. Factory Method ===" << std::endl;
    ConcreteCreator<int> creator;
    AbstractWorkItem<int>* made = creator.createWorkItem();
    std::cout << "  Made '" << made->getName() << "' in state " << made->getStateName() << std::endl;
    delete made;

    std::cout << std::endl << "=== 9. Chain of Responsibility ===" << std::endl;
    ConcreteHandler<int>* lead = new ConcreteHandler<int>("Team lead", 3);
    lead->setSuccessor(new ConcreteHandler<int>("Manager", 7));
    lead->handleRequest(1);
    lead->handleRequest(5);
    lead->handleRequest(9);
    delete lead;

    std::cout << std::endl << "=== 10. Strategy ===" << std::endl;
   
    WorkItem<int> task(30, "Task", 120, nullptr);
    task.addTask("T1", 8, 10);
    task.addTask("T2", 5, 10);
    task.addTask("T3", 10, 10);
    task.addTask("T4", 2, 10);
    
    task.updateTaskScore(3, 7); // Updates T4 from 2 to 7

    ConcreteStrategyA<int> avgStrategy;
    ConcreteStrategyB<int> maxStrategy;
    ConcreteStrategyC<int> minStrategy;

    avgStrategy.algorithm(&task);
    maxStrategy.algorithm(&task);
    minStrategy.algorithm(&task);

    std::cout << std::endl << "=== 11. Adapter ===" << std::endl;
    Adaptee external;
    Adapter adapter(&external);
    Target* target = &adapter;
    target->request();


    return 0;
}
