#ifndef ABSTRACTEXAMPAPER_H
#define ABSTRACTEXAMPAPER_H

#include "ExamComponent.h"

#include <string>
#include <vector>

class PaperState;
class Marker;

class AbstractExamPaper : public ExamComponent {
protected:
    PaperState* state;
    std::string moduleCode;
    int examDuration;
    double marks;
    int year;    //THIS HAS A YEAR PARAMETER NOW
    std::vector<Marker*> observers;
public:
    virtual ~AbstractExamPaper() = default;
    AbstractExamPaper(std::string code, int duration, double initialMarks, int year)
        : state(nullptr), moduleCode(code), examDuration(duration), marks(initialMarks), year(year){}

    virtual AbstractExamPaper* clonePaper() = 0;
    virtual PaperState* getState() = 0;
    virtual void setState(PaperState* state) = 0;
    virtual void mark() = 0;
    double getMarks();
    int getYear() const;
    double getBonusMarks() override;
    int getExtraTime() override;

    void attach(Marker* observer);
    void detach(Marker* observer);    //OBSERVER FUNCTIONS
    void notify();

};

#endif
