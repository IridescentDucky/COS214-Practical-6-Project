#include "ExamDecorator.h"

ExamDecorator::ExamDecorator(ExamComponent* component)
    : component(component) {
}

double ExamDecorator::getBonusMarks() {
    return component->getBonusMarks();
}

int ExamDecorator::getExtraTime() {
    return component->getExtraTime();
}
