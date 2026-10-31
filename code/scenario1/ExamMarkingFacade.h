#ifndef EXAMMARKINGFACADE_H
#define EXAMMARKINGFACADE_H

#include "ExamPaperCollection.h"
#include "ExamPaperCreator.h"
#include "ExamResultsStrategy.h"
#include "ExamStatisticsOriginator.h"
#include "Markers.h"
#include "StatisticsCaretaker.h"

#include <memory>
#include <string>
#include <vector>

class ExamPaper;
class ExamStatsStrategy;

class ExamMarkingFacade {
private:
    int year;
    ExamPaperCreator creator;
    ExamPaperCollection papers;
    Tutor tutor;
    AssistantLecturer assistantLecturer;
    Lecturer lecturer;
    ExamStatisticsOriginator statistics;
    StatisticsCaretaker history;
    std::vector<std::unique_ptr<ExamPaper> > ownedPapers;

    ExamPaper* find(int paperIndex) const;
    bool ownsPaper(const ExamPaper* paper) const;

public:
    ExamMarkingFacade();
    explicit ExamMarkingFacade(int year);
    ~ExamMarkingFacade();
    ExamMarkingFacade(const ExamMarkingFacade&) = delete;
    ExamMarkingFacade& operator=(const ExamMarkingFacade&) = delete;

    int createExamPaper(const std::string& moduleCode, int duration);
    ExamPaper* createExamPaper(
        const std::string& moduleCode,
        int examDuration,
        double initialMarks,
        int year);
    bool addQuestion(int paperIndex, const std::string& question, double maximumMarks);
    bool captureMarks(int paperIndex);
    void assignPaper(ExamPaper* paper, Marker* chainHead);
    void captureMarks(ExamPaper* paper);
    ExamMetricResult calculateMetric(const ExamPaper* paper, ExamMetric metric) const;
    double generateStatistics(ExamStatsStrategy* strategy);
    const StatisticsMemento* generateStatistics(int year);
    void undoStatistics();
};

#endif
