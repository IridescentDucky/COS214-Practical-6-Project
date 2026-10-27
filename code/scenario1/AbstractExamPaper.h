#ifndef ABSTRACTEXAMPAPER_H
#define ABSTRACTEXAMPAPER_H

#include <string>
class PaperState;

class AbstractExamPaper {
    
protected:
    PaperState* state;
    std::string moduleCode;
    int examDuration;
    double marks;
    
public:
    virtual ~AbstractExamPaper() = default;
    AbstractExamPaper(std::string code, int duration, double initialMarks): state(NULL), moduleCode(code), examDuration(duration), marks(initialMarks) {}
    
    virtual double getMarks() = 0;
    virtual AbstractExamPaper* clonePaper() = 0;
    virtual PaperState* getState() = 0;
    virtual void setState(PaperState* state) = 0;
    virtual void mark() = 0;
};

#endif
