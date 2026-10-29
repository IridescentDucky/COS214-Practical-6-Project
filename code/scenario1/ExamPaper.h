#ifndef EXAMPAPER_H
#define EXAMPAPER_H

#include "AbstractExamPaper.h"

class PaperState;

class ExamPaper : public AbstractExamPaper{
        
public:
    ExamPaper(std::string code, int duration, double initialMarks);
    
    AbstractExamPaper* clonePaper() override;
    void mark() override;
    PaperState* getState() override;
    void setState(PaperState* state) override;
    
    virtual std::string getModuleCode() override;
    
    // Question vector functions:
    void addQuestion(const std::string& question) override;
    const std::vector<std::string>& getQuestions() const override;
    const std::string& getQuestion(int index) const override;
    int getQuestionCount() const override;
};

#endif
