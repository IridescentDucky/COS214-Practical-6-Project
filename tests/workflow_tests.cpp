#include "Caretaker.h"
#include "ConcreteWorkflowFactory1.h"
#include "ConcreteWorkflowFactory2.h"
#include "Observer.h"
#include "TIVIDY.h"
#include "WorkItem.h"
#include "WorkflowMediator.h"

#include <gtest/gtest.h>

#include <typeinfo>

namespace
{
class CountingObserver : public Observer
{
public:
    CountingObserver() : updateCount(0) {}

    void update() override
    {
        ++updateCount;
    }

    int updateCount;
};

void complete(WorkItem& item)
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
    WorkItem item(1, "Task", 5, nullptr);
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
    WorkItem item(1, "Late task", 1, nullptr);
    item.handleState();
    item.handleState();
    item.addTimeSpent(2);
    item.handleState();

    EXPECT_EQ("InProgress", item.getStateName());
}

TEST(StateTest, PauseAndResumeRestoreInProgress)
{
    WorkItem item(1, "Task", 5, nullptr);
    item.handleState();
    item.handleState();
    item.paused();
    ASSERT_EQ("Paused", item.getStateName());
    item.resume();
    EXPECT_EQ("InProgress", item.getStateName());
}

TEST(MediatorTest, RejectsInvalidAndDuplicateDependencies)
{
    WorkflowMediator mediator;
    mediator.addWorkItem(new WorkItem(1, "First", 5, &mediator));
    mediator.addWorkItem(new WorkItem(2, "Second", 5, &mediator));

    EXPECT_TRUE(mediator.addDependency(1, 2));
    EXPECT_FALSE(mediator.addDependency(1, 2));
    EXPECT_FALSE(mediator.addDependency(1, 1));
    EXPECT_FALSE(mediator.addDependency(1, 99));
}

TEST(MediatorTest, CompletionActivatesEveryCreatedDependentOnlyOnce)
{
    WorkflowMediator mediator;
    WorkItem* predecessor = new WorkItem(1, "First", 5, &mediator);
    WorkItem* firstDependent = new WorkItem(2, "Second", 5, &mediator);
    WorkItem* secondDependent = new WorkItem(3, "Third", 5, &mediator);
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
    WorkItem item(1, "Task", 5, nullptr);
    Caretaker caretaker;
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
    WorkItem item(1, "Task", 5, nullptr);
    CountingObserver observer;
    item.attach(&observer);

    item.handleState();
    EXPECT_EQ(1, observer.updateCount);

    item.detach(&observer);
    item.handleState();
    EXPECT_EQ(1, observer.updateCount);
}

TEST(AbstractFactoryTest, EachFactoryCreatesItsOwnProductFamily)
{
    ConcreteWorkflowFactory1 firstFactory;
    ConcreteWorkflowFactory2 secondFactory;
    AbstractWorkflowInstanceA* firstA = firstFactory.createWorkflowInstanceA();
    AbstractWorkflowInstanceB* firstB = firstFactory.createWorkflowInstanceB();
    AbstractWorkflowInstanceA* secondA = secondFactory.createWorkflowInstanceA();
    AbstractWorkflowInstanceB* secondB = secondFactory.createWorkflowInstanceB();

    EXPECT_NE(typeid(*firstA), typeid(*secondA));
    EXPECT_NE(typeid(*firstB), typeid(*secondB));

    delete firstA;
    delete firstB;
    delete secondA;
    delete secondB;
}

TEST(AbstractFactoryTest, NullFactoryIsIgnoredSafely)
{
    TIVIDY tividy;
    EXPECT_NO_THROW(tividy.runWorkflow(nullptr));
}

TEST(WorkflowEndToEndTest, FacadeCompletesPredecessorAndActivatesDependent)
{
    TIVIDY tividy;
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
