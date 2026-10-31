#include "ExamPaper.h"
#include "Marker.h"
#include "States.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>
#include <string>

ExamPaper::ExamPaper(std::string code, int duration, double initialMarks, int year)
    : AbstractExamPaper(code, duration, initialMarks, year),
      marker(nullptr),
      tutorMarks(0.0),
      assistantLecturerMarks(0.0),
      physicalError(false),
      markDiscrepancy(false),
      manualEscalation(false),
      escalationReviewed(false) {}

AbstractExamPaper* ExamPaper::clonePaper() {
    ExamPaper* copy = new ExamPaper(moduleCode, examDuration, marks, year);
    copy->questions = questions;
    copy->questionMaximumMarks = questionMaximumMarks;
    copy->questionMarks = questionMarks;
    copy->questionMarksCaptured = questionMarksCaptured;
    copy->tutorMarks = tutorMarks;
    copy->assistantLecturerMarks = assistantLecturerMarks;
    copy->physicalError = physicalError;
    copy->markDiscrepancy = markDiscrepancy;
    copy->manualEscalation = manualEscalation;
    copy->escalationReviewed = escalationReviewed;

    if (state == nullptr) {
        copy->setState(nullptr);
    } else if (dynamic_cast<WrittenState*>(state) != nullptr) {
        copy->setState(new WrittenState(copy));
    } else if (dynamic_cast<DeliveredState*>(state) != nullptr) {
        copy->setState(new DeliveredState(copy));
    } else if (dynamic_cast<MarkingState*>(state) != nullptr) {
        copy->setState(new MarkingState(copy));
    } else if (dynamic_cast<ExceptionState*>(state) != nullptr) {
        copy->setState(new ExceptionState(copy));
    } else if (dynamic_cast<PausedState*>(state) != nullptr) {
        copy->setState(new PausedState(copy));
    } else if (dynamic_cast<ValidatedState*>(state) != nullptr) {
        copy->setState(new ValidatedState(copy));
    } else if (dynamic_cast<MarkedState*>(state) != nullptr) {
        copy->setState(new MarkedState(copy));
    } else if (dynamic_cast<CapturedState*>(state) != nullptr) {
        copy->setState(new CapturedState(copy));
    } else if (dynamic_cast<FailedState*>(state) != nullptr) {
        copy->setState(new FailedState(copy));
    } else {
        delete copy;
        throw std::logic_error("Cannot clone an unsupported paper state.");
    }

    return copy;
}

void ExamPaper::mark() {
    if (state == nullptr) {
        std::cerr << "[ExamPaper] Cannot mark archived paper "
                  << moduleCode << "." << std::endl;
        return;
    }
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

    notify();
}

void ExamPaper::setMarker(Marker* marker) {
    if (marker == nullptr) {
        std::cout << "[ExamPaper] Cannot assign a null marker to "
                  << moduleCode << "." << std::endl;
        return;
    }

    if (this->marker == marker) {
        return;
    }
    if (this->marker != nullptr) {
        detach(this->marker);
    }

    this->marker = marker;
    attach(marker);
}

void ExamPaper::detach(Marker* observer) {
    AbstractExamPaper::detach(observer);
    if (marker == observer) {
        marker = nullptr;
    }
}

PaperState* ExamPaper::getState() {
    return this->state;
}

void ExamPaper::setState(PaperState* state) {
    if (this->state == state) {
        return;
    }

    std::cout << "[ExamPaper] Changing state for " << this->moduleCode << std::endl;
    delete this->state;
    this->state = state;
}

const std::string& ExamPaper::getModuleCode() const {
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

int ExamPaper::getExamDuration() const {
    return examDuration;
}

bool ExamPaper::isMarked() const {
    return !questionMarks.empty() &&
        std::find(questionMarksCaptured.begin(), questionMarksCaptured.end(), false) ==
            questionMarksCaptured.end();
}

bool ExamPaper::setQuestionMark(int index, double awardedMarks) {
    if (index < 0 || static_cast<std::size_t>(index) >= questions.size() ||
        !std::isfinite(awardedMarks) || awardedMarks < 0.0 ||
        awardedMarks > questionMaximumMarks[static_cast<std::size_t>(index)]) {
        return false;
    }

    questionMarks[static_cast<std::size_t>(index)] = awardedMarks;
    questionMarksCaptured[static_cast<std::size_t>(index)] = true;

    const int tutorQuestionCount = getTutorQuestionCount();
    tutorMarks = 0.0;
    assistantLecturerMarks = 0.0;
    for (std::size_t questionIndex = 0; questionIndex < questionMarks.size(); ++questionIndex) {
        if (!questionMarksCaptured[questionIndex]) {
            continue;
        }

        if (static_cast<int>(questionIndex) < tutorQuestionCount) {
            tutorMarks += questionMarks[questionIndex];
        } else {
            assistantLecturerMarks += questionMarks[questionIndex];
        }
    }

    if (isMarked()) {
        marks = tutorMarks + assistantLecturerMarks;
    }
    return true;
}

double ExamPaper::getQuestionMark(int index) const {
    if (!hasQuestionMark(index)) {
        return 0.0;
    }
    return questionMarks[static_cast<std::size_t>(index)];
}

double ExamPaper::getQuestionMaximumMarks(int index) const {
    if (index < 0 || static_cast<std::size_t>(index) >= questionMaximumMarks.size()) {
        return 0.0;
    }
    return questionMaximumMarks[static_cast<std::size_t>(index)];
}

bool ExamPaper::hasQuestionMark(int index) const {
    return index >= 0 &&
        static_cast<std::size_t>(index) < questionMarksCaptured.size() &&
        questionMarksCaptured[static_cast<std::size_t>(index)];
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
    questionMarks.push_back(0.0);
    questionMarksCaptured.push_back(false);
    marks = 0.0;
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
