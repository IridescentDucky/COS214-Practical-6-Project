#ifndef ABSTRACTEXAMPAPER_H
#define ABSTRACTEXAMPAPER_H

#include <vector>
#include <string>

class PaperState;

class AbstractExamPaper {
    
protected:
    PaperState* state;
    std::string moduleCode;
    int examDuration;
    double marks;
    std::vector<std::string> questions;
    
public:
    virtual ~AbstractExamPaper() = default;
    AbstractExamPaper(std::string code, int duration, double initialMarks): state(NULL), moduleCode(code), examDuration(duration), marks(initialMarks) {}
    
    virtual AbstractExamPaper* clonePaper() = 0;
    virtual PaperState* getState() = 0;
    virtual void setState(PaperState* state) = 0;
    virtual void mark() = 0;
    
    virtual std::string getModuleCode() =0;
    
    // Question vector functions:
    virtual void addQuestion(const std::string& question) = 0;
    virtual const std::vector<std::string>& getQuestions() const = 0;
    virtual const std::string& getQuestion(int index) const = 0;
    virtual int getQuestionCount() const = 0;
};

#endif
