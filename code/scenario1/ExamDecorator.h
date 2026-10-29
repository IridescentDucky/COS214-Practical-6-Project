#ifndef EXAMDECORATOR_H
#define EXAMDECORATOR_H

#include "ExamComponent.h"

class ExamDecorator : public ExamComponent {
protected:
    explicit ExamDecorator(ExamComponent* component);

    ExamComponent* component;

public:
    void mark() override = 0;
    double getMarks() override;
    ~ExamDecorator() override = default;
};

#endif
