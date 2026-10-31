#include "BonusScoreDecorator.h"
#include "BonusTimeDecorator.h"
#include "Caretaker.h"
#include "Composite.h"
#include "ConcreteCreator.h"
#include "ConcreteHandler.h"
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

TEST(DecoratorTest, BonusesStackOnTheWrappedWorkItem)
{
    WorkItem<int> item(1, "Task", 5, nullptr);
    BonusScoreDecorator<int> scored(&item, 10, 2);
    BonusTimeDecorator<int> extended(&scored, 3);

    EXPECT_EQ(20, extended.getScore());
    EXPECT_EQ(3, extended.getTime());
    EXPECT_EQ(0, item.getScore());
}

TEST(CompositeTest, GroupAddsUpItsChildren)
{
    WorkItem<int> second(2, "Second", 5, nullptr);
    Composite<int> group("Sprint");
    WorkItem<int>* first = new WorkItem<int>(1, "First", 5, nullptr);
    group.add(first);
    group.add(new BonusTimeDecorator<int>(&second, 4));

    EXPECT_EQ(4, group.getTime());
    EXPECT_TRUE(group.getChild(0) == first);
    EXPECT_TRUE(group.getChild(5) == nullptr);
}

TEST(FactoryMethodTest, CreatorMakesANewWorkItem)
{
    ConcreteCreator<int> creator;
    AbstractWorkItem<int>* item = creator.createWorkItem();

    ASSERT_TRUE(item != nullptr);
    EXPECT_EQ("Created", item->getStateName());
    delete item;
}

TEST(ChainOfResponsibilityTest, RequestGoesToFirstHandlerThatCanTakeIt)
{
    ConcreteHandler<int>* lead = new ConcreteHandler<int>("Lead", 3);
    lead->setSuccessor(new ConcreteHandler<int>("Manager", 7));

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
