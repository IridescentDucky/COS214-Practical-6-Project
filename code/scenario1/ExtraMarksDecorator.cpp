#include "ExtraMarksDecorator.h"

ExtraMarksDecorator::ExtraMarksDecorator(
    ExamComponent* component,
    double extraMarks)
    : ExamDecorator(component), extraMarks(extraMarks) {
}

double ExtraMarksDecorator::getBonusMarks() {
    return component->getBonusMarks() +extraMarks;
}
