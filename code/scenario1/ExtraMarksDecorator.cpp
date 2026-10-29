#include "ExtraMarksDecorator.h"

ExtraMarksDecorator::ExtraMarksDecorator(
    ExamComponent* component,
    double extraMarks)
    : ExamDecorator(component), extraMarks(extraMarks) {
}

void ExtraMarksDecorator::mark() {
    // TODO: delegate marking and apply extraMarks.
}

double ExtraMarksDecorator::getMarks() {
    // TODO: include extraMarks in the wrapped component's total.
    return 0.0;
}
