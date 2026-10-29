#include "ConcessionDecorator.h"

ConcessionDecorator::ConcessionDecorator(
    ExamComponent* component,
    int additionalTime)
    : ExamDecorator(component), additionalTime(additionalTime) {
}

void ConcessionDecorator::mark() {
    // TODO: apply the concession before delegating marking.
}

int ConcessionDecorator::getAdjustedDuration() {
    // TODO: return the wrapped paper duration plus additionalTime.
    return 0;
}
