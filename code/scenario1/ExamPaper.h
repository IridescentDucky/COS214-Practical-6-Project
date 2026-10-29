#ifndef EXAMPAPER_H
#define EXAMPAPER_H

#include "AbstractExamPaper.h"

class PaperState;

class ExamPaper : public AbstractExamPaper{
        
public:
    ExamPaper(std::string code, int duration, double initialMarks);
    AbstractExamPaper* clonePaper() override;
    void mark() override;
    PaperState* getState() override;
    void setState(PaperState* state) override;
};

#endif
