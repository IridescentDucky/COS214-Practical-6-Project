#include "ExamPaper.h"
#include <iostream>
#include <vector>
#include <string>

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

std::string ExamPaper::getModuleCode(){
    
    std::cout << "[ExamPaper] module code: " << this->moduleCode << std::endl;
    return this->moduleCode;
}

// Question vector functions:

void ExamPaper::addQuestion(const std::string& question) {
    
    std::cout << "[ExamPaper] Added a question." << std::endl;
    questions.push_back(question);
}

const std::vector<std::string>& ExamPaper::getQuestions() const {
    
    std::cout << "[ExamPaper] Retrieving all questions." << std::endl;
    return questions;
}

const std::string& ExamPaper::getQuestion(int index) const {
    
    if (index < 0 || static_cast<std::size_t>(index) >= questions.size()) {
        std::cout << "[ExamPaper] Question index: " << index << " out of bounds." << std::endl;
        static const std::string emptStr = "";
        return emptStr;
    }
    
    std::cout << "[ExamPaper] Retrieving question: " << index << std::endl;
    return questions[static_cast<std::size_t>(index)];
}

int ExamPaper::getQuestionCount() const {
    
    std::cout << "[ExamPaper] Getting question count: " << static_cast<int>(questions.size()) << std::endl;
    return static_cast<int>(questions.size());
}
