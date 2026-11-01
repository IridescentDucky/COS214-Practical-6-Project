#include "BonusScoreDecorator.h"
#include "BonusTimeDecorator.h"
#include "Caretaker.h"
#include "Composite.h"
#include "ConcreteStrategyB.h"
#include "Iterator.h"
#include "TIVIDY.h"
#include "StatsOriginator.h"
#include "StatsCaretaker.h"

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
    tividy.scoreTask(redesign, 0, 9);
    tividy.scoreTask(redesign, 1, 7);
    tividy.scoreTask(redesign, 2, 10);
    tividy.submitWork(redesign, "second pass");
    tividy.advanceWork(redesign);
    tividy.printStatus();

    
    std::cout << std::endl << "=== 10. Storing stats and retrieving them (Strategy and Memento) ===" << std::endl;
    
    AbstractWorkItem<int>* designItemForStats = findItem(tividy, design);
    StatsOriginator<int> statsOriginator(2026);
    StatsCaretaker statsCaretaker;

    // calculating stats and printing the state and then storing the stats
    statsOriginator.calculateStats(designItemForStats);
    statsOriginator.printState();
    statsCaretaker.saveMemento(statsOriginator.createMemento());

    // writing in new object with different stats
    statsOriginator.calculateStats(buildItem);
    statsOriginator.printState();

    // restoring the initial object's stats
    statsOriginator.restoreFromMemento(statsCaretaker.getMemento());
    statsOriginator.printState();
    
    // testing getMemento()
    StatsMemento* retrieved = statsCaretaker.getMemento();
    std::cout << "[Main]: testing if memento was got: " << retrieved->getYear() << std::endl;

    std::cout << std::endl << "=== 11. Same engine, another workflow: exam marking (configuration, not new classes) ===" << std::endl;
    TIVIDY<int> exams;
    std::vector<std::pair<std::string, int> > markers;
    markers.push_back(std::make_pair(std::string("Tutor"), 2));
    markers.push_back(std::make_pair(std::string("Assistant lecturer"), 4));
    markers.push_back(std::make_pair(std::string("Lecturer"), 7));
    markers.push_back(std::make_pair(std::string("Module coordinator"), 10));
    exams.setEscalationLevels(markers);
    exams.setExternalSystem("Student records system");
    int memo = exams.createWorkItem("Memo", 2);
    int first = exams.createWorkItem("Paper u24675815", 3);
    exams.addTask(first, "Question 1", 10);
    exams.addTask(first, "Question 2", 15);
    int second = exams.createFromTemplate(exams.saveAsTemplate(first), "Paper u25108582");
    exams.addDependency(memo, first);
    exams.addDependency(memo, second);
    exams.advanceWork(memo);
    exams.advanceWork(memo);
    exams.submitWork(memo, "memo final");
    exams.advanceWork(memo);
    exams.advanceWork(first);
    exams.scoreTask(first, 0, 8);
    exams.submitWork(first, "");
    exams.advanceWork(first);
    exams.scoreTask(first, 1, 12);
    exams.submitWork(first, "");
    exams.advanceWork(first);
    exams.advanceWork(second);
    exams.logTime(second, 5);
    exams.printStatus();

    return 0;
}
