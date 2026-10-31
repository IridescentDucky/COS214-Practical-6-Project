#include "ConcessionDecorator.h"
#include "ExamMarkingFacade.h"
#include "ExamPaper.h"
#include "ExamPaperGroup.h"
#include "ExtraMarksDecorator.h"
#include "Marker.h"
#include "Markers.h"
#include "States.h"
#include "StatisticsMemento.h"

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

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

TEST(Scenario1StrategyTest, CalculatesQuestionPercentagesAndAllocatedMinuteRate)
{
    ExamMarkingFacade facade;
    ExamPaper* paper = facade.createExamPaper("COS214", 180, 0.0, 2026);
    paper->addQuestion("Question 1", 10.0);
    paper->addQuestion("Question 2", 5.0);
    EXPECT_FALSE(
        facade.calculateMetric(paper, ExamMetric::TopQuestion).valid);
    ASSERT_TRUE(paper->setQuestionMark(0, 9.0));
    ASSERT_TRUE(paper->setQuestionMark(1, 4.0));

    const ExamMetricResult top =
        facade.calculateMetric(paper, ExamMetric::TopQuestion);
    const ExamMetricResult lowest =
        facade.calculateMetric(paper, ExamMetric::LowestQuestion);
    const ExamMetricResult rate =
        facade.calculateMetric(paper, ExamMetric::MarksPerAllocatedMinute);

    ASSERT_TRUE(top.valid);
    EXPECT_EQ("Top question percentage", top.metricName);
    EXPECT_EQ("Question 1", top.question);
    EXPECT_DOUBLE_EQ(90.0, top.value);
    ASSERT_TRUE(lowest.valid);
    EXPECT_EQ("Question 2", lowest.question);
    EXPECT_DOUBLE_EQ(80.0, lowest.value);
    ASSERT_TRUE(rate.valid);
    EXPECT_DOUBLE_EQ(13.0 / 180.0, rate.value);
}

TEST(Scenario1StrategyTest, RejectsInvalidScoresAndRequiresEveryQuestionToBeMarked)
{
    ExamPaper paper("COS214", 180, 0.0, 2026);
    paper.addQuestion("Question 1", 10.0);
    paper.addQuestion("Question 2", 5.0);

    EXPECT_FALSE(paper.setQuestionMark(0, 11.0));
    EXPECT_FALSE(paper.setQuestionMark(2, 1.0));
    ASSERT_TRUE(paper.setQuestionMark(0, 0.0));
    EXPECT_FALSE(paper.isMarked());
    ASSERT_TRUE(paper.setQuestionMark(1, 5.0));
    EXPECT_TRUE(paper.isMarked());
}

TEST(Scenario1MarkingTest, CapturesIndividualQuestionScoresAndZeroForUnanswered)
{
    Tutor tutor("T001", "Tutor");
    AssistantLecturer assistant("A001", "Assistant");
    tutor.setNext(&assistant);

    ExamPaper paper("COS214", 180, 0.0, 2026);
    paper.addQuestion("Question 1", 10.0);
    paper.addQuestion("Question 2", 10.0);
    paper.setMarker(&tutor);

    std::istringstream enteredMarks(" \nn\nn\nn\n5\nn\nn\nn\n");
    std::streambuf* originalInput = std::cin.rdbuf(enteredMarks.rdbuf());
    paper.mark();
    std::cin.rdbuf(originalInput);

    EXPECT_TRUE(paper.isMarked());
    EXPECT_DOUBLE_EQ(0.0, paper.getQuestionMark(0));
    EXPECT_DOUBLE_EQ(5.0, paper.getQuestionMark(1));
    EXPECT_DOUBLE_EQ(5.0, paper.getMarks());
}

TEST(Scenario1StatisticsTest, AggregatesFixedOutcomeBandsAndSnapshotsPaperMetrics)
{
    ExamMarkingFacade facade;
    const double scores[] = {49.0, 50.0, 75.0};
    for (int index = 0; index < 3; ++index) {
        ExamPaper* paper = facade.createExamPaper("COS214", 60, 0.0, 2026);
        paper->addQuestion("Question 1", 100.0);
        ASSERT_TRUE(paper->setQuestionMark(0, scores[index]));
    }
    ExamPaper* unresolvedPaper = facade.createExamPaper("COS214", 60, 0.0, 2026);
    unresolvedPaper->addQuestion("Question 1", 100.0);
    ASSERT_TRUE(unresolvedPaper->setQuestionMark(0, 100.0));
    unresolvedPaper->flagManualEscalation();

    const StatisticsMemento* snapshot = facade.generateStatistics(2026);
    ASSERT_NE(nullptr, snapshot);
    EXPECT_DOUBLE_EQ(100.0 / 3.0, snapshot->getPassRate());
    EXPECT_DOUBLE_EQ((49.0 + 50.0 + 75.0) / 3.0, snapshot->getAverageMark());
    EXPECT_DOUBLE_EQ(100.0 / 3.0, snapshot->getDistinctionRate());
    EXPECT_DOUBLE_EQ(100.0 / 3.0, snapshot->getFailureRate());
    ASSERT_EQ(9U, snapshot->getPaperMetrics().size());
    EXPECT_TRUE(snapshot->getPaperMetrics()[0].valid);
    EXPECT_EQ(ExamMetric::TopQuestion, snapshot->getPaperMetrics()[0].metric);
    EXPECT_DOUBLE_EQ(49.0, snapshot->getPaperMetrics()[0].value);
}
