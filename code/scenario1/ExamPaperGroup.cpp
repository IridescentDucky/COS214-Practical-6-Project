#include "ExamPaperGroup.h"

void ExamPaperGroup::mark() {
    // TODO: mark each child component.
}

void ExamPaperGroup::add(ExamComponent* element) {
    elements.push_back(element);
}

void ExamPaperGroup::remove(ExamComponent* element) {
    for (auto it = elements.begin(); it != elements.end(); ++it) {
        if (*it == element) {
            elements.erase(it);
            return;
        }
    }
}

double ExamPaperGroup::getMarks() {
    // TODO: aggregate marks from child components.
    return 0.0;
}

double ExamPaperGroup::getBonusMarks() {
    double total = 0.0;
    for (ExamComponent* element : elements) {
        total += element->getBonusMarks();
    }
    return total;
}

int ExamPaperGroup::getExtraTime() {
    int total = 0;
    for (ExamComponent* element : elements) {
        total += element->getExtraTime();
    }
    return total;
}
