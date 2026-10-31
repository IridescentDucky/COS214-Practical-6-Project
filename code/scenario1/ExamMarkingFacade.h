#ifndef EXAMMARKINGFACADE_H
#define EXAMMARKINGFACADE_H

#include "ExamPaperCollection.h"
#include "ExamPaperCreator.h"

#include <memory>
#include <string>
#include <vector>

class ExamPaper;
class Marker;

class ExamMarkingFacade {
private:
    ExamPaperCreator creator;
    ExamPaperCollection papers;
    std::vector<std::unique_ptr<ExamPaper> > ownedPapers;

    bool ownsPaper(const ExamPaper* paper) const;

public:
    ~ExamMarkingFacade();

    ExamPaper* createExamPaper(
        const std::string& moduleCode,
        int examDuration,
        double initialMarks,
        int year);
    void assignPaper(ExamPaper* paper, Marker* chainHead);
    void captureMarks(ExamPaper* paper);
    void generateStatistics();
};

#endif
