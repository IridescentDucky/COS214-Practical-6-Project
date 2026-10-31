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
    std::vector<Marker*> observers;
    std::string moduleCode;
    int examDuration;
    double marks;
    int year;
public:
    virtual ~AbstractExamPaper();
    AbstractExamPaper(std::string code, int duration, double initialMarks, int year);

    virtual AbstractExamPaper* clonePaper() = 0;
    virtual PaperState* getState() = 0;
    virtual void setState(PaperState* state) = 0;
    virtual void mark() = 0;
    double getMarks() const;
    int getYear() const;
    double getBonusMarks() override;
    int getExtraTime() override;

    void attach(Marker* observer);
    virtual void detach(Marker* observer);
    void notify();
};

#endif
