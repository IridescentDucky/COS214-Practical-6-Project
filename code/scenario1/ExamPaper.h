#ifndef EXAMPAPER_H
#define EXAMPAPER_H

#include "AbstractExamPaper.h"
class PaperState;

class ExamPaper : public AbstractExamPaper{
    
public:
    ExamPaper(std::string code, int duration, double initialMarks);
    
    ExamPaper* clonePaper();
    void mark();
    PaperState* getState();
    void setState(PaperState* state);
};

#endif
