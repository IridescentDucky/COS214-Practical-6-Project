#ifndef EXAMPAPER_H
#define EXAMPAPER_H

#include "AbstractExamPaper.h"

#include <string>
#include <vector>

class PaperState;
class Marker;

class ExamPaper : public AbstractExamPaper {
private:
    std::vector<std::string> questions;
    std::vector<double> questionMaximumMarks;
    Marker* marker;
    double tutorMarks;
    double assistantLecturerMarks;
    bool tutorMarksCaptured;
    bool assistantLecturerMarksCaptured;
    bool physicalError;
    bool markDiscrepancy;
    bool manualEscalation;
    bool escalationReviewed;

public:
    ExamPaper(std::string code, int duration, double initialMarks, int year);

    AbstractExamPaper* clonePaper() override;
    void mark() override;
    void setMarker(Marker* marker);
    void detach(Marker* observer) override;
    double getMaximumMarks() const;
    double getTutorMaximumMarks() const;
    double getAssistantLecturerMaximumMarks() const;
    int getTutorQuestionCount() const;
    double getTutorMarks() const;
    double getAssistantLecturerMarks() const;
    bool setTutorMarks(double marks);
    bool setAssistantLecturerMarks(double marks);
    void flagPhysicalError();
    void flagMarkDiscrepancy();
    void flagManualEscalation();
    bool hasPhysicalError() const;
    bool hasMarkDiscrepancy() const;
    bool hasManualEscalation() const;
    bool hasPendingEscalation() const;
    bool resolveEscalation(double finalMarks);
    PaperState* getState() override;
    void setState(PaperState* state) override;

    std::string getModuleCode();
    void addQuestion(const std::string& question);
    void addQuestion(const std::string& question, double maximumMarks);
    const std::vector<std::string>& getQuestions() const;
    const std::string& getQuestion(int index) const;
    int getQuestionCount() const;
};

#endif
