#include "ExamMarkingFacade.h"

int main() {
    ExamMarkingFacade facade;
    facade.createExamPaper();
    facade.assignPaper();
    facade.captureMarks();
    facade.generateStatistics();
    return 0;
}
