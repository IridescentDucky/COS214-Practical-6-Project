#ifndef CONCESSIONDECORATOR_H
#define CONCESSIONDECORATOR_H

#include "ExamDecorator.h"

class ConcessionDecorator : public ExamDecorator {
private:
    int extraTime;

public:
    ConcessionDecorator(ExamComponent* component, int extraTime);
    int getExtraTime() override;
};

#endif
