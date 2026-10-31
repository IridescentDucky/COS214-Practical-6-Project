#include "BonusScoreDecorator.h"
#include "BonusTimeDecorator.h"
#include "Caretaker.h"
#include "Composite.h"
#include "ConcreteStrategyB.h"
#include "Iterator.h"
#include "TIVIDY.h"

#include <iostream>

AbstractWorkItem<int>* findItem(const TIVIDY<int>& tividy, int id)
{
    AbstractWorkItem<int>* found = nullptr;
    Iterator<int>* it = tividy.createIterator();
    while (it->hasNext() && found == nullptr)
    {
        AbstractWorkItem<int>* item = it->next();
        if (item->getId() == id)
        {
            found = item;
        }
    }
    delete it;
    return found;
}

int main()
{
    TIVIDY<int> tividy;

    std::cout << "=== 1. Create work (Facade + Factory Method + Prototype) ===" << std::endl;
    int design = tividy.createWorkItem("Design", 5);
    tividy.addTask(design, "Wireframes", 8, 10);
    tividy.addTask(design, "User flows", 5, 10);
    tividy.addTask(design, "Style guide", 10, 10);
    int designTemplate = tividy.saveAsTemplate(design);
    int build = tividy.createWorkItem("Build", 5);
    tividy.addTask(build, "API", 7, 10);
    int test = tividy.createWorkItem("Test", 5);

    std::cout << std::endl << "=== 2. Dependencies and lifecycle (Mediator + State + Observer) ===" << std::endl;
    tividy.addDependency(design, build);
    tividy.addDependency(design, test);
    tividy.pauseWork(design);
    tividy.advanceWork(design);
    tividy.advanceWork(design);
    tividy.pauseWork(design);
    tividy.resumeWork(design);
    tividy.logTime(design, 4);

    std::cout << std::endl << "=== 3. Completion (Strategy + Adapter + Mediator) ===" << std::endl;
    tividy.submitWork(design, "approved design");
    tividy.advanceWork(design);

    std::cout << std::endl << "=== 4. Status (Iterator) ===" << std::endl;
    tividy.printStatus();

    std::cout << std::endl << "=== 5. Overdue work escalates (Observer + Chain of Responsibility) ===" << std::endl;
    tividy.advanceWork(test);
    tividy.logTime(test, 7);
    tividy.logTime(test, 2);
    tividy.logTime(test, 4);
    tividy.logTime(test, 7);
    tividy.logTime(test, 7);
    tividy.logTime(test, 5);

    std::cout << std::endl << "=== 6. Undo a change (Memento) ===" << std::endl;
    AbstractWorkItem<int>* buildItem = findItem(tividy, build);
    Caretaker<int> history;
    history.addMemento(buildItem->createMemento());
    tividy.advanceWork(build);
    buildItem->exception();
    buildItem->setMemento(history.getMemento(0));
    std::cout << "  Build is back in " << tividy.getWorkItemState(build) << std::endl;

    std::cout << std::endl << "=== 7. Extra score and time (Decorator) ===" << std::endl;
    BonusScoreDecorator<int> scored(buildItem, 10, 2);
    BonusTimeDecorator<int> extended(&scored, 3);
    extended.display();
    std::cout << "  Score: " << buildItem->getScore() << " -> " << extended.getScore() << ", time allowed: " << buildItem->getTime() << " -> " << extended.getTime() << std::endl;

    std::cout << std::endl << "=== 8. Group work (Composite) ===" << std::endl;
    Composite<int> sprint("Sprint 1");
    sprint.add(buildItem);
    sprint.add(findItem(tividy, test));
    sprint.display();
    std::cout << "  Sprint total score: " << sprint.getScore() << ", time allowed: " << sprint.getTime() << std::endl;

    std::cout << std::endl << "=== 9. Reuse a template and swap the scoring rule (Prototype + Strategy) ===" << std::endl;
    int redesign = tividy.createFromTemplate(designTemplate);
    tividy.setStrategy(new ConcreteStrategyB<int>());
    tividy.advanceWork(redesign);
    tividy.advanceWork(redesign);
    tividy.submitWork(redesign, "second pass");
    tividy.advanceWork(redesign);
    tividy.printStatus();

    return 0;
}
