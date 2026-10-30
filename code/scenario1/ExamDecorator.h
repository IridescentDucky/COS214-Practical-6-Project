#ifndef EXAMDECORATOR_H
#define EXAMDECORATOR_H

#include "ExamComponent.h"

class ExamDecorator : public ExamComponent {
protected:
    ExamComponent* component;

public:
     ExamDecorator(ExamComponent* component);
     virtual double getBonusMarks();
     virtual int getExtraTime();
    ~ExamDecorator() override = default;
};

#endif
