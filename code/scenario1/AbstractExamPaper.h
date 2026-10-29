#ifndef ABSTRACTEXAMPAPER_H
#define ABSTRACTEXAMPAPER_H

#include "ExamComponent.h"

#include <string>

class PaperState;

class AbstractExamPaper : public ExamComponent {
protected:
    PaperState* state;
    std::string moduleCode;
    int examDuration;
    double marks;

public:
    virtual ~AbstractExamPaper() = default;
    AbstractExamPaper(std::string code, int duration, double initialMarks)
        : state(nullptr), moduleCode(code), examDuration(duration), marks(initialMarks) {}

    virtual AbstractExamPaper* clonePaper() = 0;
    virtual PaperState* getState() = 0;
    virtual void setState(PaperState* state) = 0;
    void mark() override = 0;
    double getMarks() override;
};

#endif
