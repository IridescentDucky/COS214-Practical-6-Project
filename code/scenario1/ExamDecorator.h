#ifndef EXAMDECORATOR_H
#define EXAMDECORATOR_H

#include "ExamComponent.h"

class ExamDecorator : public ExamComponent {
protected:
    ExamComponent* component;

public:
     ExamDecorator(ExamComponent* component);
     virtual int getBonusMarks();
     virtual int getExtraTime();
    ~ExamDecorator() override = default;
};

#endif
