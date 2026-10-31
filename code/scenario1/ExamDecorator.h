#ifndef EXAMDECORATOR_H
#define EXAMDECORATOR_H

#include "ExamComponent.h"

class ExamDecorator : public ExamComponent {
protected:
    ExamComponent* component;

public:
     ExamDecorator(ExamComponent* component);
     double getBonusMarks() override;
     int getExtraTime() override;
    ~ExamDecorator() override = default;
};

#endif
