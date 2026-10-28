#ifndef EXAMCOMPONENT_H
#define EXAMCOMPONENT_H

#include "AbstractExamPaper.h"

class ExamComponent : AbstractExamPaper {
public:
    virtual void mark();
    virtual double getMarks();

    virtual void add(ExamComponent* e);
    virtual void remove(ExamComponent* e);
};

#endif