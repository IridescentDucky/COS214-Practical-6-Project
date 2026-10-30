#include "ConcessionDecorator.h"

ConcessionDecorator::ConcessionDecorator(
    ExamComponent* component,
    int extraTime)
    : ExamDecorator(component), extraTime(extraTime) {
}

int ConcessionDecorator::getExtraTime() {
    return component->getExtraTime() + extraTime;
}
