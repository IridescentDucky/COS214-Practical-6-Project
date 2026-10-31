#include "ConcessionDecorator.h"
#include "ExamMarkingFacade.h"
#include "ExamPaper.h"
#include "ExamPaperGroup.h"
#include "ExtraMarksDecorator.h"
#include "Marker.h"
#include "States.h"

#include <gtest/gtest.h>

namespace
{
class CountingMarker : public Marker
{
public:
    CountingMarker() : Marker("M001", "Counting marker"), updateCount(0), handleCount(0) {}

    void handle(AbstractExamPaper*) override
    {
        ++handleCount;
    }

    void update() override
    {
        ++updateCount;
        if (paper != nullptr) {
            handle(paper);
        }
    }

    AbstractExamPaper* observedPaper() const
    {
        return paper;
    }

    int updateCount;
    int handleCount;
};
}

TEST(Scenario1StateTest, ExecutesNormalPaperLifecycle)
{
    ExamPaper paper("COS214", 180, 0.0, 2026);
    ASSERT_TRUE(dynamic_cast<WrittenState*>(paper.getState()) != nullptr);

    paper.getState()->nextState();
    ASSERT_TRUE(dynamic_cast<DeliveredState*>(paper.getState()) != nullptr);

    paper.getState()->nextState();
    ASSERT_TRUE(dynamic_cast<MarkingState*>(paper.getState()) != nullptr);

    paper.getState()->pause();
    ASSERT_TRUE(dynamic_cast<PausedState*>(paper.getState()) != nullptr);

    paper.getState()->resumeMarking();
    ASSERT_TRUE(dynamic_cast<MarkingState*>(paper.getState()) != nullptr);

    paper.getState()->completeMarking();
    ASSERT_TRUE(dynamic_cast<MarkedState*>(paper.getState()) != nullptr);

    paper.getState()->nextState();
    ASSERT_TRUE(dynamic_cast<CapturedState*>(paper.getState()) != nullptr);

    paper.getState()->nextState();
    EXPECT_EQ(nullptr, paper.getState());
}

TEST(Scenario1ComponentTest, DecoratorsAndGroupsAggregateBonusMarksAndExtraTime)
{
    ExamPaper paper("COS214", 180, 0.0, 2026);
    ExtraMarksDecorator extraMarks(&paper, 2.5);
    ConcessionDecorator concession(&extraMarks, 30);
    ExamPaperGroup group;
    group.add(&paper);
    group.add(&concession);

    EXPECT_DOUBLE_EQ(2.5, group.getBonusMarks());
    EXPECT_EQ(30, group.getExtraTime());
}

TEST(Scenario1ObserverTest, PaperNotifiesItsAttachedChainHead)
{
    ExamPaper paper("COS214", 180, 0.0, 2026);
    paper.addQuestion("Question 1", 10.0);
    CountingMarker marker;
    paper.setMarker(&marker);

    paper.mark();

    EXPECT_EQ(1, marker.updateCount);
    EXPECT_EQ(1, marker.handleCount);
    EXPECT_EQ(&paper, marker.observedPaper());

    paper.detach(&marker);
    EXPECT_EQ(nullptr, marker.observedPaper());
}

TEST(Scenario1FacadeTest, OwnsCreatedPaperAndAssignsMarkerChain)
{
    CountingMarker marker;
    {
        ExamMarkingFacade facade;
        ExamPaper* paper = facade.createExamPaper("COS214", 180, 0.0, 2026);
        paper->addQuestion("Question 1", 10.0);

        facade.assignPaper(paper, &marker);
        facade.captureMarks(paper);

        EXPECT_EQ(1, marker.updateCount);
        EXPECT_EQ(1, marker.handleCount);
    }

    EXPECT_EQ(nullptr, marker.observedPaper());
}
