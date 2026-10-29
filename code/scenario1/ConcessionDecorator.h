#ifndef CONCESSIONDECORATOR_H
#define CONCESSIONDECORATOR_H

#include "ExamDecorator.h"

class ConcessionDecorator : public ExamDecorator {
private:
    int additionalTime;

public:
    ConcessionDecorator(ExamComponent* component, int additionalTime);
    void mark() override;
    int getAdjustedDuration();
};

#endif
