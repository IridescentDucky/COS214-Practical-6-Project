#include "ExamDecorator.h"

ExamDecorator::ExamDecorator(ExamComponent* component)
    : component(component) {
}

void ExamDecorator::mark() {
    // TODO: delegate marking to the wrapped component.
}

double ExamDecorator::getMarks() {
    // TODO: delegate mark retrieval to the wrapped component.
    return 0.0;
}
