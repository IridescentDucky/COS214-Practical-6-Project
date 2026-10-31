#ifndef EXAMMARKINGFACADE_H
#define EXAMMARKINGFACADE_H

#include "ExamPaperCollection.h"
#include "ExamPaperCreator.h"
#include "ExamStatisticsOriginator.h"
#include "Markers.h"
#include "StatisticsCaretaker.h"

#include <string>

class ExamPaper;
class ExamStatsStrategy;

class ExamMarkingFacade
{
public:
    explicit ExamMarkingFacade(int year);
    ~ExamMarkingFacade();
    ExamMarkingFacade(const ExamMarkingFacade&) = delete;
    ExamMarkingFacade& operator=(const ExamMarkingFacade&) = delete;

    int createExamPaper(const std::string& moduleCode, int duration);
    bool addQuestion(int paperIndex, const std::string& question, double maximumMarks);
    bool captureMarks(int paperIndex);
    double generateStatistics(ExamStatsStrategy* strategy);
    void undoStatistics();

private:
    ExamPaper* find(int paperIndex) const;

    int year;
    ExamPaperCreator creator;
    ExamPaperCollection papers;
    Tutor tutor;
    AssistantLecturer assistantLecturer;
    Lecturer lecturer;
    ExamStatisticsOriginator statistics;
    StatisticsCaretaker history;
};

#endif
