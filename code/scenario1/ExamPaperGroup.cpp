#include "ExamPaperGroup.h"

void ExamPaperGroup::mark() {
    // something
}

void ExamPaperGroup::add(ExamComponent* e) {
    elements.push_back(e);
}

void ExamPaperGroup::remove(ExamComponent* e) {
    elements.remove(e);
}

// getchild?