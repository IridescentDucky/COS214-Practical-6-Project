#include "ExamMarkingFacade.h"
#include "ExamPaper.h"
#include "Markers.h"
#include "PaperState.h"

int main() {
    Tutor tutor("T001", "Tutor");
    AssistantLecturer assistant("A001", "Assistant Lecturer");
    tutor.setNext(&assistant);

    ExamMarkingFacade facade;
    ExamPaper* paper = facade.createExamPaper("COS214", 180, 0.0, 2026);
    paper->addQuestion("Question 1", 50.0);
    paper->addQuestion("Question 2", 50.0);

    facade.assignPaper(paper, &tutor);
    paper->getState()->nextState();
    paper->getState()->nextState();
    facade.captureMarks(paper);
    paper->getState()->completeMarking();
    paper->getState()->nextState();
    paper->getState()->nextState();
    return 0;
}
