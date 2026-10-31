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
    std::vector<double> questionMarks;
    std::vector<bool> questionMarksCaptured;
    Marker* marker;
    double tutorMarks;
    double assistantLecturerMarks;
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
    bool setQuestionMark(int index, double marks);
    double getQuestionMark(int index) const;
    double getQuestionMaximumMarks(int index) const;
    bool hasQuestionMark(int index) const;
    bool isMarked() const;
    int getExamDuration() const;
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

    const std::string& getModuleCode() const;
    void addQuestion(const std::string& question);
    void addQuestion(const std::string& question, double maximumMarks);
    const std::vector<std::string>& getQuestions() const;
    const std::string& getQuestion(int index) const;
    int getQuestionCount() const;
};

#endif
