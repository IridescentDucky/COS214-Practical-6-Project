#include "ExamPaperGroup.h"

void ExamPaperGroup::add(ExamComponent* element) {
    if (element != nullptr) {
        elements.push_back(element);
    }
}

void ExamPaperGroup::remove(ExamComponent* element) {
    for (auto it = elements.begin(); it != elements.end(); ++it) {
        if (*it == element) {
            elements.erase(it);
            return;
        }
    }
}

double ExamPaperGroup::getBonusMarks() {
    double bonusMarks = 0.0;
    for (ExamComponent* element : elements) {
        bonusMarks += element->getBonusMarks();
    }
    return bonusMarks;
}

int ExamPaperGroup::getExtraTime() {
    int extraTime = 0;
    for (ExamComponent* element : elements) {
        extraTime += element->getExtraTime();
    }
    return extraTime;
}