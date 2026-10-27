#include "ExamPaper.h"
#include <iostream>

ExamPaper::ExamPaper(std::string code, int duration, double initialMarks): AbstractExamPaper(code, duration, initialMarks) {}

AbstractExamPaper* ExamPaper::clonePaper(){
    return new ExamPaper(*this);
}

void ExamPaper::mark(){
    
    return;
}

PaperState* ExamPaper::getState(){
    
    std::cout << "[ExamPaper] " << this->moduleCode << " is in state: " << this->state << std::endl;
    return this->state;
}

void ExamPaper::setState(PaperState* state) {
    
    if (state == NULL) {
        std::cout << "[ExamPaper] Cannot set a null state." << std::endl;
        return;
    }
    
    std::cout << "[ExamPaper] Changing state for " << this->moduleCode << std::endl;
    this->state = state;
}
