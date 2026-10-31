#include "BonusScoreDecorator.h"
#include "BonusTimeDecorator.h"
#include "Caretaker.h"
#include "Composite.h"
#include "ConcreteCreator.h"
#include "ConcreteHandlerA.h"
#include "ConcreteHandlerB.h"
#include "ConcreteHandlerC.h"
#include "ConcreteHandlerD.h"
#include "ConcreteHandlerE.h"
#include "ConcreteStrategyB.h"
#include "PrototypeManager.h"
#include "Iterator.h"
#include "TaskEscalationManager.h"
#include "TIVIDY.h"
#include "WorkItem.h"
#include "WorkflowMediator.h"

#include <gtest/gtest.h>

#include <sstream>
#include <vector>

namespace
{
class CountingObserver : public TaskEscalationManager<int>
{
public:
    CountingObserver() : TaskEscalationManager<int>(0), updateCount(0) {}

    void handleRequest(int) override
    {
    }

    void update() override
    {
        ++updateCount;
    }

    int updateCount;
};

void complete(WorkItem<int>& item)
{
    item.handleState();
    item.handleState();
    item.set("valid result");
    item.handleState();
    item.handleState();
}

void completeThroughFacade(TIVIDY<int>& tividy, int id)
{
    tividy.advanceWork(id);
    tividy.advanceWork(id);
    tividy.submitWork(id, "done");
    tividy.advanceWork(id);
}

AbstractWorkItem<int>* findThroughIterator(const TIVIDY<int>& tividy, int id)
{
    AbstractWorkItem<int>* found = nullptr;
    Iterator<int>* it = tividy.createIterator();
    while (it->hasNext())
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

class OutputCapture
{
public:
    OutputCapture() : original(std::cout.rdbuf(buffer.rdbuf()))
    {
    }

    ~OutputCapture()
    {
        std::cout.rdbuf(original);
    }

    std::string text() const
    {
        return buffer.str();
    }

    bool contains(const std::string& part) const
    {
        return buffer.str().find(part) != std::string::npos;
    }

private:
    std::ostringstream buffer;
    std::streambuf* original;
};
}

TEST(StateTest, ValidDataCompletesAndInvalidDataReturnsToInProgress)
{
    WorkItem<int> item(1, "Task", 5, nullptr);
    item.handleState();
    item.handleState();
    item.handleState();
    ASSERT_EQ("Validation", item.getStateName());

    item.handleState();
    EXPECT_EQ("InProgress", item.getStateName());

    item.set("result");
    item.handleState();
    ASSERT_EQ("Validation", item.getStateName());
    item.handleState();
    EXPECT_EQ("Completed", item.getStateName());
}

TEST(StateTest, DeadlineGuardPreventsValidation)
{
    WorkItem<int> item(1, "Late task", 1, nullptr);
    item.handleState();
    item.handleState();
    item.addTimeSpent(2);
    item.handleState();

    EXPECT_EQ("InProgress", item.getStateName());
}

TEST(StateTest, PauseAndResumeRestoreInProgress)
{
    WorkItem<int> item(1, "Task", 5, nullptr);
    item.handleState();
    item.handleState();
    item.paused();
    ASSERT_EQ("Paused", item.getStateName());
    item.resume();
    EXPECT_EQ("InProgress", item.getStateName());
}

TEST(MediatorTest, RejectsInvalidAndDuplicateDependencies)
{
    WorkflowMediator<int> mediator;
    mediator.addWorkItem(new WorkItem<int>(1, "First", 5, &mediator));
    mediator.addWorkItem(new WorkItem<int>(2, "Second", 5, &mediator));

    EXPECT_TRUE(mediator.addDependency(1, 2));
    EXPECT_FALSE(mediator.addDependency(1, 2));
    EXPECT_FALSE(mediator.addDependency(1, 1));
    EXPECT_FALSE(mediator.addDependency(1, 99));
}

TEST(MediatorTest, CompletionActivatesEveryCreatedDependentOnlyOnce)
{
    WorkflowMediator<int> mediator;
    WorkItem<int>* predecessor = new WorkItem<int>(1, "First", 5, &mediator);
    WorkItem<int>* firstDependent = new WorkItem<int>(2, "Second", 5, &mediator);
    WorkItem<int>* secondDependent = new WorkItem<int>(3, "Third", 5, &mediator);
    mediator.addWorkItem(predecessor);
    mediator.addWorkItem(firstDependent);
    mediator.addWorkItem(secondDependent);
    ASSERT_TRUE(mediator.addDependency(1, 2));
    ASSERT_TRUE(mediator.addDependency(1, 3));

    complete(*predecessor);

    EXPECT_EQ("Completed", predecessor->getStateName());
    EXPECT_EQ("Delivered", firstDependent->getStateName());
    EXPECT_EQ("Delivered", secondDependent->getStateName());

    mediator.notify(predecessor);
    EXPECT_EQ("Delivered", firstDependent->getStateName());
    EXPECT_EQ("Delivered", secondDependent->getStateName());
}

TEST(MediatorTest, IncompletePredecessorDoesNotActivateDependents)
{
    WorkflowMediator<int> mediator;
    WorkItem<int>* predecessor = new WorkItem<int>(1, "First", 5, &mediator);
    WorkItem<int>* dependent = new WorkItem<int>(2, "Second", 5, &mediator);
    mediator.addWorkItem(predecessor);
    mediator.addWorkItem(dependent);
    ASSERT_TRUE(mediator.addDependency(1, 2));

    mediator.notify(predecessor);
    EXPECT_EQ("Created", dependent->getStateName());

    complete(*predecessor);
    EXPECT_EQ("Completed", predecessor->getStateName());
    EXPECT_EQ("Delivered", dependent->getStateName());
}

TEST(FacadeTest, WorkflowsKeepItemsAndDependenciesInstanceLocal)
{
    TIVIDY<int> first;
    TIVIDY<int> second;
    const int firstPredecessor = first.createWorkItem("First design", 5);
    const int firstDependent = first.createWorkItem("First build", 5);
    const int secondPredecessor = second.createWorkItem("Second design", 5);
    const int secondDependent = second.createWorkItem("Second build", 5);
    ASSERT_EQ(firstPredecessor, secondPredecessor);
    ASSERT_EQ(firstDependent, secondDependent);
    ASSERT_TRUE(first.addDependency(firstPredecessor, firstDependent));

    completeThroughFacade(first, firstPredecessor);

    EXPECT_EQ("Completed", first.getWorkItemState(firstPredecessor));
    EXPECT_EQ("Delivered", first.getWorkItemState(firstDependent));
    EXPECT_EQ("Created", second.getWorkItemState(secondPredecessor));
    EXPECT_EQ("Created", second.getWorkItemState(secondDependent));
}

TEST(MementoTest, RestoresAnIndependentStateSnapshot)
{
    WorkItem<int> item(1, "Task", 5, nullptr);
    Caretaker<int> caretaker;
    item.handleState();
    ASSERT_EQ("Delivered", item.getStateName());
    caretaker.addMemento(item.createMemento());
    item.handleState();
    ASSERT_EQ("InProgress", item.getStateName());

    item.setMemento(caretaker.getMemento(0));
    EXPECT_EQ("Delivered", item.getStateName());
    item.handleState();
    EXPECT_EQ("InProgress", item.getStateName());
}

TEST(ObserverTest, AttachedObserverIsNotifiedAndDetachedObserverIsNot)
{
    WorkItem<int> item(1, "Task", 5, nullptr);
    CountingObserver observer;
    item.attach(&observer);

    item.handleState();
    EXPECT_EQ(1, observer.updateCount);

    item.detach(&observer);
    item.handleState();
    EXPECT_EQ(1, observer.updateCount);
}

TEST(ObserverTest, AttachingTwiceStillNotifiesOnce)
{
    WorkItem<int> item(1, "Task", 5, nullptr);
    CountingObserver observer;
    item.attach(&observer);
    item.attach(&observer);

    item.handleState();
    EXPECT_EQ(1, observer.updateCount);
}

TEST(ObserverTest, AttachingToAnotherItemMovesTheObserver)
{
    WorkItem<int> first(1, "First", 5, nullptr);
    WorkItem<int> second(2, "Second", 5, nullptr);
    CountingObserver observer;
    first.attach(&observer);
    second.attach(&observer);

    first.handleState();
    EXPECT_EQ(0, observer.updateCount);

    second.handleState();
    EXPECT_EQ(1, observer.updateCount);
    EXPECT_TRUE(observer.getWorkItem() == &second);
}

TEST(ObserverTest, DestroyedObserverDetachesItself)
{
    WorkItem<int> item(1, "Task", 5, nullptr);
    {
        CountingObserver observer;
        item.attach(&observer);
    }

    item.handleState();
    EXPECT_EQ("Delivered", item.getStateName());
}

TEST(ObserverTest, DestroyedWorkItemReleasesItsObservers)
{
    CountingObserver observer;
    {
        WorkItem<int> item(1, "Task", 5, nullptr);
        item.attach(&observer);
    }

    EXPECT_TRUE(observer.getWorkItem() == nullptr);
}

TEST(DecoratorTest, BonusesStackOnTheWrappedWorkItem)
{
    WorkItem<int> item(1, "Task", 5, nullptr);
    item.addTask("Part A", 6, 10);
    item.addTask("Part B", 4, 10);
    BonusScoreDecorator<int> scored(&item, 10, 2);
    BonusTimeDecorator<int> extended(&scored, 3);

    EXPECT_EQ(10, item.getScore());
    EXPECT_EQ(5, item.getTime());
    EXPECT_EQ(40, extended.getScore());
    EXPECT_EQ(8, extended.getTime());
}

TEST(CompositeTest, GroupAddsUpItsChildren)
{
    WorkItem<int> first(1, "First", 5, nullptr);
    WorkItem<int> second(2, "Second", 5, nullptr);
    first.addTask("Spec", 7, 10);
    second.addTask("Code", 9, 10);
    BonusTimeDecorator<int> extended(&second, 4);
    Composite<int> group("Sprint");
    group.add(&first);
    group.add(&extended);

    EXPECT_EQ(16, group.getScore());
    EXPECT_EQ(14, group.getTime());
    EXPECT_TRUE(group.getChild(0) == &first);
    EXPECT_TRUE(group.getChild(5) == nullptr);
}

TEST(CompositeTest, GroupDoesNotDeleteWorkItemsOwnedByTheFacade)
{
    TIVIDY<int> tividy;
    tividy.createWorkItem("Design", 5);
    Iterator<int>* it = tividy.createIterator();
    AbstractWorkItem<int>* item = it->next();
    delete it;
    {
        Composite<int> group("Sprint");
        group.add(item);
    }

    EXPECT_EQ("Created", tividy.getWorkItemState(1));
}

TEST(FactoryMethodTest, CreatorMakesTheRequestedWorkItem)
{
    ConcreteCreator<int> creator;
    AbstractWorkItem<int>* item = creator.createWorkItem(7, "Report", 3, nullptr);

    ASSERT_TRUE(item != nullptr);
    EXPECT_EQ(7, item->getId());
    EXPECT_EQ("Report", item->getName());
    EXPECT_EQ("Created", item->getStateName());
    delete item;
}

TEST(FactoryMethodTest, FacadeCreatesItemsThroughTheFactory)
{
    TIVIDY<int> tividy;
    std::ostringstream output;
    std::streambuf* original = std::cout.rdbuf(output.rdbuf());
    int id = tividy.createWorkItem("Design", 5);
    std::cout.rdbuf(original);

    EXPECT_EQ(1, id);
    EXPECT_NE(std::string::npos, output.str().find("[Factory] Creating WorkItem 'Design'"));
}

TEST(ChainOfResponsibilityTest, ReplacingASuccessorUsesTheNewOne)
{
    ConcreteHandlerA<int>* lead = new ConcreteHandlerA<int>("Lead", 3);
    lead->setSuccessor(new ConcreteHandlerA<int>("Manager", 7));
    lead->setSuccessor(new ConcreteHandlerA<int>("Director", 10));

    std::ostringstream output;
    std::streambuf* original = std::cout.rdbuf(output.rdbuf());
    lead->handleRequest(9);
    std::cout.rdbuf(original);
    delete lead;

    EXPECT_EQ("Lead passed the request on\nDirector handled the request\n", output.str());
}

TEST(ChainOfResponsibilityTest, SuccessorThatWouldLoopIsRejected)
{
    ConcreteHandlerA<int>* lead = new ConcreteHandlerA<int>("Lead", 3);
    ConcreteHandlerA<int>* manager = new ConcreteHandlerA<int>("Manager", 7);
    lead->setSuccessor(manager);

    std::ostringstream output;
    std::streambuf* original = std::cout.rdbuf(output.rdbuf());
    manager->setSuccessor(lead);
    lead->setSuccessor(lead);
    lead->handleRequest(9);
    std::cout.rdbuf(original);
    delete lead;

    EXPECT_NE(std::string::npos, output.str().find("The request could not be handled"));
}

TEST(ChainOfResponsibilityTest, RequestGoesToFirstHandlerThatCanTakeIt)
{
    ConcreteHandlerA<int>* lead = new ConcreteHandlerA<int>("Lead", 3);
    lead->setSuccessor(new ConcreteHandlerA<int>("Manager", 7));

    std::ostringstream output;
    std::streambuf* original = std::cout.rdbuf(output.rdbuf());
    lead->handleRequest(1);
    lead->handleRequest(5);
    lead->handleRequest(9);
    std::cout.rdbuf(original);
    delete lead;

    EXPECT_EQ("Lead handled the request\n"
              "Lead passed the request on\nManager handled the request\n"
              "Lead passed the request on\nThe request could not be handled\n", output.str());
}

TEST(FacadeTest, NullOrUnknownIdsAreIgnoredSafely)
{
    TIVIDY<int> tividy;
    EXPECT_NO_THROW(tividy.advanceWork(42));
    EXPECT_EQ("", tividy.getWorkItemState(42));
}

TEST(WorkflowEndToEndTest, FacadeCompletesPredecessorAndActivatesDependent)
{
    TIVIDY<int> tividy;
    const int predecessor = tividy.createWorkItem("Design", 5);
    const int dependent = tividy.createWorkItem("Build", 5);
    ASSERT_TRUE(tividy.addDependency(predecessor, dependent));

    tividy.advanceWork(predecessor);
    tividy.advanceWork(predecessor);
    tividy.submitWork(predecessor, "approved");
    tividy.advanceWork(predecessor);

    EXPECT_EQ("Completed", tividy.getWorkItemState(predecessor));
    EXPECT_EQ("Delivered", tividy.getWorkItemState(dependent));
}

TEST(IteratorTest, VisitsEveryWorkItemInOrderThenStops)
{
    WorkflowMediator<int> mediator;
    mediator.addWorkItem(new WorkItem<int>(1, "First", 5, &mediator));
    mediator.addWorkItem(new WorkItem<int>(2, "Second", 5, &mediator));
    mediator.addWorkItem(new WorkItem<int>(3, "Third", 5, &mediator));

    Iterator<int>* it = mediator.createIterator();
    std::vector<int> ids;
    while (it->hasNext())
    {
        ids.push_back(it->next()->getId());
    }

    std::vector<int> expected;
    expected.push_back(1);
    expected.push_back(2);
    expected.push_back(3);
    EXPECT_EQ(expected, ids);
    EXPECT_TRUE(it->next() == nullptr);
    delete it;
}

TEST(IteratorTest, EmptyMediatorHasNothingToVisit)
{
    WorkflowMediator<int> mediator;
    Iterator<int>* it = mediator.createIterator();

    EXPECT_FALSE(it->hasNext());
    EXPECT_TRUE(it->next() == nullptr);
    delete it;
}

TEST(EscalationTest, OnTimeWorkIsObservedButNotEscalated)
{
    TIVIDY<int> tividy;
    int id = tividy.createWorkItem("Design", 5);
    OutputCapture output;
    tividy.advanceWork(id);
    tividy.logTime(id, 5);

    EXPECT_TRUE(output.contains("Team lead was notified that Design is Delivered"));
    EXPECT_FALSE(output.contains("handled the request"));
}

TEST(EscalationTest, OverdueWorkGoesFurtherUpTheChainTheLaterItIs)
{
    TIVIDY<int> tividy;
    int id = tividy.createWorkItem("Design", 5);
    const int extraTime[] = { 7, 2, 5, 6, 6, 10 };
    const char* expected[] = {
        "Team lead handled the request",
        "Manager handled the request",
        "Department head handled the request",
        "Director handled the request",
        "Executive handled the request",
        "The request could not be handled"
    };
    for (int step = 0; step < 6; ++step)
    {
        OutputCapture output;
        tividy.logTime(id, extraTime[step]);
        EXPECT_TRUE(output.contains(expected[step])) << "after logging " << extraTime[step] << " more: " << output.text();
    }
}

TEST(ChainOfResponsibilityTest, FiveHandlerTypesCanFormOneChain)
{
    ConcreteHandlerA<int>* first = new ConcreteHandlerA<int>("A", 1);
    ConcreteHandlerB<int>* second = new ConcreteHandlerB<int>("B", 2);
    ConcreteHandlerC<int>* third = new ConcreteHandlerC<int>("C", 3);
    ConcreteHandlerD<int>* fourth = new ConcreteHandlerD<int>("D", 4);
    first->setSuccessor(second);
    second->setSuccessor(third);
    third->setSuccessor(fourth);
    fourth->setSuccessor(new ConcreteHandlerE<int>("E", 5));

    OutputCapture output;
    first->handleRequest(4);
    std::string text = output.text();
    delete first;

    EXPECT_EQ("A passed the request on\nB handled the request", text);
}

TEST(CompletionTest, MediatorScoresNotifiesExternalSystemAndDeliversDependents)
{
    TIVIDY<int> tividy;
    int design = tividy.createWorkItem("Design", 5);
    int build = tividy.createWorkItem("Build", 5);
    tividy.addTask(design, "Wireframes", 6, 10);
    tividy.addTask(design, "Flows", 8, 10);
    tividy.addDependency(design, build);

    OutputCapture output;
    completeThroughFacade(tividy, design);

    EXPECT_TRUE(output.contains("[Strategy A] Calculated overall average score: 7"));
    EXPECT_TRUE(output.contains("(Adaptee) Specified request recieved"));
    EXPECT_EQ("Delivered", tividy.getWorkItemState(build));
}

TEST(CompletionTest, SwappingTheStrategyChangesHowCompletedWorkIsScored)
{
    TIVIDY<int> tividy;
    int design = tividy.createWorkItem("Design", 5);
    tividy.addTask(design, "Wireframes", 6, 10);
    tividy.addTask(design, "Flows", 9, 10);
    tividy.setStrategy(new ConcreteStrategyB<int>());

    OutputCapture output;
    completeThroughFacade(tividy, design);

    EXPECT_TRUE(output.contains("[Strategy B] Calculated max score: 9"));
}

TEST(PrototypeTest, TemplateCloneIsANewIndependentItem)
{
    TIVIDY<int> tividy;
    int design = tividy.createWorkItem("Design", 5);
    tividy.addTask(design, "Wireframes", 6, 10);
    completeThroughFacade(tividy, design);
    int templateIndex = tividy.saveAsTemplate(design);

    int first = tividy.createFromTemplate(templateIndex);
    int second = tividy.createFromTemplate(templateIndex);
    AbstractWorkItem<int>* firstItem = findThroughIterator(tividy, first);
    firstItem->updateTaskScore(0, 1);
    AbstractWorkItem<int>* secondItem = findThroughIterator(tividy, second);

    EXPECT_EQ(0, templateIndex);
    EXPECT_EQ(2, first);
    EXPECT_EQ(3, second);
    EXPECT_EQ("Design", firstItem->getName());
    EXPECT_EQ("Created", firstItem->getStateName());
    EXPECT_EQ(1, secondItem->getTaskCount());
    EXPECT_EQ(6, secondItem->getTask(0).score);
}

TEST(PrototypeTest, UnknownTemplatesAndItemsAreRejected)
{
    TIVIDY<int> tividy;
    EXPECT_EQ(-1, tividy.saveAsTemplate(42));
    EXPECT_EQ(-1, tividy.createFromTemplate(0));
    EXPECT_EQ(-1, tividy.createFromTemplate(-1));
}

TEST(PrototypeTest, ManagerOwnsAndRemovesItsPrototypes)
{
    PrototypeManager<int> manager;
    AbstractWorkItem<int>* prototype = new WorkItem<int>(1, "Template", 5, nullptr);
    manager.addPrototype(prototype);
    manager.addPrototype(prototype);
    EXPECT_EQ(1, manager.getPrototypeCount());
    EXPECT_TRUE(manager.getPrototype(0) == prototype);
    EXPECT_TRUE(manager.getPrototype(1) == nullptr);

    manager.removePrototype(prototype);
    EXPECT_EQ(0, manager.getPrototypeCount());
    manager.addPrototype(new WorkItem<int>(2, "Kept", 5, nullptr));
}

TEST(FacadeTest, InvalidTimeAndTasksAreRejected)
{
    TIVIDY<int> tividy;
    int id = tividy.createWorkItem("Design", 5);
    tividy.logTime(id, 0);
    tividy.logTime(id, -3);
    tividy.addTask(id, "Too high", 11, 10);
    tividy.addTask(id, "Negative", -1, 10);

    AbstractWorkItem<int>* item = findThroughIterator(tividy, id);
    EXPECT_EQ(0, item->getOverdue());
    EXPECT_EQ(0, item->getTaskCount());
}
