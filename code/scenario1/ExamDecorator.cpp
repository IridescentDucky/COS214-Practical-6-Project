#include "ExamDecorator.h"

ExamDecorator::ExamDecorator(ExamComponent* component)
    : component(component) {
}

int ExamDecorator::getBonusMarks() {
    return component->getBonusMarks();
}

int ExamDecorator::getExtraTime() {
    return component->getExtraTime();
}
