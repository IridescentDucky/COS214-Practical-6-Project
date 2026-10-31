#include "ExamPaper.h"
#include "Marker.h"

#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
#include <string>

double AbstractExamPaper::getMarks() {
    return marks;
}

int AbstractExamPaper::getYear() const {
    return year;
}

double AbstractExamPaper::getBonusMarks() {
    return 0.0;
}

int AbstractExamPaper::getExtraTime() {
    return 0;
}

void AbstractExamPaper::attach(Marker* observer) {
    if (observer != nullptr) {
        observers.push_back(observer);
    }
}

void AbstractExamPaper::detach(Marker* observer) {
    for (std::vector<Marker*>::iterator it = observers.begin(); it != observers.end(); ++it) {
        if (*it == observer) {
            observers.erase(it);
            return;
        }
    }
}

void AbstractExamPaper::notify() {
    for (Marker* observer : observers) {
        observer->setExamPaper(this);
        observer->update();
    }
}

ExamPaper::ExamPaper(std::string code, int duration, double initialMarks, int year)
    : AbstractExamPaper(code, duration, initialMarks, year),
      marker(nullptr),
      tutorMarks(0.0),
      assistantLecturerMarks(0.0),
      tutorMarksCaptured(false),
      assistantLecturerMarksCaptured(false),
      physicalError(false),
      markDiscrepancy(false),
      manualEscalation(false),
      escalationReviewed(false) {}

AbstractExamPaper* ExamPaper::clonePaper() {
    return new ExamPaper(*this);
}

void ExamPaper::mark() {
    if (marker == nullptr) {
        std::cout << "[ExamPaper] Cannot mark " << moduleCode
                  << ": no marker has been assigned." << std::endl;
        return;
    }
    if (questions.empty()) {
        std::cout << "[ExamPaper] Cannot mark " << moduleCode
                  << ": no questions have been added." << std::endl;
        return;
    }

    marker->handle(this);
}

void ExamPaper::setMarker(Marker* marker) {
    if (marker == nullptr) {
        std::cout << "[ExamPaper] Cannot assign a null marker to "
                  << moduleCode << "." << std::endl;
        return;
    }

    this->marker = marker;
}

PaperState* ExamPaper::getState() {
    std::cout << "[ExamPaper] " << this->moduleCode << " is in state: " << this->state << std::endl;
    return this->state;
}

void ExamPaper::setState(PaperState* state) {
    if (state == nullptr) {
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

double ExamPaper::getMaximumMarks() const {
    double total = 0.0;
    for (double maximum : questionMaximumMarks) {
        total += maximum;
    }
    return total;
}

int ExamPaper::getTutorQuestionCount() const {
    const double target = getMaximumMarks() / 2.0;
    double cumulative = 0.0;
    double bestDifference = std::numeric_limits<double>::max();
    int bestCount = 0;

    for (std::size_t count = 0; count <= questionMaximumMarks.size(); ++count) {
        const double difference = std::fabs(cumulative - target);
        if (difference < bestDifference) {
            bestDifference = difference;
            bestCount = static_cast<int>(count);
        }

        if (count < questionMaximumMarks.size()) {
            cumulative += questionMaximumMarks[count];
        }
    }

    // On an exact tie, keep the earlier boundary so the AssistantLecturer gets the extra marks.
    return bestCount;
}

double ExamPaper::getTutorMaximumMarks() const {
    double total = 0.0;
    const int questionCount = getTutorQuestionCount();
    for (int index = 0; index < questionCount; ++index) {
        total += questionMaximumMarks[static_cast<std::size_t>(index)];
    }
    return total;
}

double ExamPaper::getAssistantLecturerMaximumMarks() const {
    return getMaximumMarks() - getTutorMaximumMarks();
}

double ExamPaper::getTutorMarks() const {
    return tutorMarks;
}

double ExamPaper::getAssistantLecturerMarks() const {
    return assistantLecturerMarks;
}

bool ExamPaper::setTutorMarks(double awardedMarks) {
    if (!std::isfinite(awardedMarks) || awardedMarks < 0.0 ||
        awardedMarks > getTutorMaximumMarks()) {
        return false;
    }

    tutorMarks = awardedMarks;
    tutorMarksCaptured = true;
    if (assistantLecturerMarksCaptured) {
        marks = tutorMarks + assistantLecturerMarks;
    }
    return true;
}

bool ExamPaper::setAssistantLecturerMarks(double awardedMarks) {
    if (!std::isfinite(awardedMarks) || awardedMarks < 0.0 ||
        awardedMarks > getAssistantLecturerMaximumMarks()) {
        return false;
    }

    assistantLecturerMarks = awardedMarks;
    assistantLecturerMarksCaptured = true;
    if (tutorMarksCaptured) {
        marks = tutorMarks + assistantLecturerMarks;
    }
    return true;
}

void ExamPaper::flagPhysicalError() {
    physicalError = true;
    escalationReviewed = false;
}

void ExamPaper::flagMarkDiscrepancy() {
    markDiscrepancy = true;
    escalationReviewed = false;
}

void ExamPaper::flagManualEscalation() {
    manualEscalation = true;
    escalationReviewed = false;
}

bool ExamPaper::hasPhysicalError() const {
    return physicalError;
}

bool ExamPaper::hasMarkDiscrepancy() const {
    return markDiscrepancy;
}

bool ExamPaper::hasManualEscalation() const {
    return manualEscalation;
}

bool ExamPaper::hasPendingEscalation() const {
    return !escalationReviewed &&
           (physicalError || markDiscrepancy || manualEscalation);
}

bool ExamPaper::resolveEscalation(double finalMarks) {
    if (!hasPendingEscalation() || !std::isfinite(finalMarks) ||
        finalMarks < 0.0 || finalMarks > getMaximumMarks()) {
        return false;
    }

    marks = finalMarks;
    escalationReviewed = true;
    return true;
}

// Question vector functions:

void ExamPaper::addQuestion(const std::string& question) {
    addQuestion(question, 1.0);
}

void ExamPaper::addQuestion(const std::string& question, double maximumMarks) {
    if (!std::isfinite(maximumMarks) || maximumMarks <= 0.0) {
        std::cout << "[ExamPaper] Question maximum marks must be greater than zero."
                  << std::endl;
        return;
    }

    std::cout << "[ExamPaper] Added a question." << std::endl;
    questions.push_back(question);
    questionMaximumMarks.push_back(maximumMarks);
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
