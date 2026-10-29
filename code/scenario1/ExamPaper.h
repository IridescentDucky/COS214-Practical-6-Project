#ifndef EXAMPAPER_H
#define EXAMPAPER_H

#include "AbstractExamPaper.h"

#include <string>
#include <vector>

class PaperState;

class ExamPaper : public AbstractExamPaper {
private:
    std::vector<std::string> questions;

public:
    ExamPaper(std::string code, int duration, double initialMarks);

    AbstractExamPaper* clonePaper() override;
    void mark() override;
    PaperState* getState() override;
    void setState(PaperState* state) override;

    std::string getModuleCode();
    void addQuestion(const std::string& question);
    const std::vector<std::string>& getQuestions() const;
    const std::string& getQuestion(int index) const;
    int getQuestionCount() const;
};

#endif
