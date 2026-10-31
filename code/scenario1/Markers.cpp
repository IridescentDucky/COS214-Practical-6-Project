#include "Markers.h"
#include "ExamPaper.h"

#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

namespace {
ExamPaper* getConcretePaper(AbstractExamPaper* paper, const char* markerName) {
    ExamPaper* examPaper = dynamic_cast<ExamPaper*>(paper);
    if (examPaper == nullptr) {
        std::cerr << "[" << markerName
                  << "] Cannot handle a null or unsupported exam paper." << std::endl;
    }
    return examPaper;
}

bool readMarks(const std::string& prompt, double maximumMarks, double& awardedMarks) {
    while (true) {
        std::cout << prompt << " (0-" << maximumMarks << "): ";
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cerr << "[Marking] Input ended before marks were entered." << std::endl;
            return false;
        }

        std::istringstream input(line);
        double value;
        std::string extra;
        if (!(input >> value) || (input >> extra) || !std::isfinite(value) ||
            value < 0.0 || value > maximumMarks) {
            std::cerr << "[Marking] Enter one numeric score between 0 and "
                      << maximumMarks << "." << std::endl;
            continue;
        }

        awardedMarks = value;
        return true;
    }
}

bool readFlag(const std::string& prompt, bool& flagged) {
    while (true) {
        std::cout << prompt << " (y/n): ";
        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cerr << "[Marking] Input ended before escalation flags were recorded."
                      << std::endl;
            return false;
        }

        for (std::string::iterator character = line.begin(); character != line.end();
             ++character) {
            *character = static_cast<char>(
                std::tolower(static_cast<unsigned char>(*character)));
        }

        if (line == "y" || line == "yes") {
            flagged = true;
            return true;
        }
        if (line == "n" || line == "no") {
            flagged = false;
            return true;
        }
        std::cerr << "[Marking] Enter y or n." << std::endl;
    }
}

bool captureEscalationFlags(ExamPaper* paper, const char* markerName) {
    bool flagged = false;
    if (!readFlag(std::string("[") + markerName +
                      "] Physical error (missing, damaged, or illegible response)?",
                  flagged)) {
        return false;
    }
    if (flagged) {
        paper->flagPhysicalError();
    }

    if (!readFlag(std::string("[") + markerName +
                      "] Mark discrepancy requiring Lecturer review?",
                  flagged)) {
        return false;
    }
    if (flagged) {
        paper->flagMarkDiscrepancy();
    }

    if (!readFlag(std::string("[") + markerName +
                      "] Manually escalate another issue?",
                  flagged)) {
        return false;
    }
    if (flagged) {
        paper->flagManualEscalation();
    }
    return true;
}
}

Tutor::Tutor(std::string id, std::string name) : Marker(id, name) {}

void Tutor::handle(AbstractExamPaper* abstractPaper) {
    ExamPaper* paper = getConcretePaper(abstractPaper, "Tutor");
    if (paper == nullptr) {
        return;
    }

    const int tutorQuestionCount = paper->getTutorQuestionCount();
    if (tutorQuestionCount > 0) {
        std::cout << "[Tutor] Mark questions 1-"
                  << tutorQuestionCount << " for "
                  << paper->getModuleCode() << "." << std::endl;
        double awardedMarks;
        if (!readMarks("[Tutor] Enter subtotal",
                       paper->getTutorMaximumMarks(), awardedMarks)) {
            return;
        }
        if (!paper->setTutorMarks(awardedMarks)) {
            std::cerr << "[Tutor] The subtotal is outside the assigned mark range."
                      << std::endl;
            return;
        }
        if (!captureEscalationFlags(paper, "Tutor")) {
            return;
        }
    } else {
        std::cout << "[Tutor] No questions were allocated; forwarding paper."
                  << std::endl;
    }
    if (!forwardToNext(paper)) {
        std::cerr << "[Tutor] No AssistantLecturer is configured to mark the remaining "
                     "questions."
                  << std::endl;
    }
}

void Tutor::update() {
    //std::cout << "[Tutor] Notified that an exam paper is ready for marking." << std::endl; just moving it
    if (paper == nullptr) {
        return;
    }
    
    std::cout << "[Tutor] Notified that an exam paper is ready for marking." << std::endl;
    handle(paper); //send it to COR
}

AssistantLecturer::AssistantLecturer(std::string id, std::string name) : Marker(id, name) {}

void AssistantLecturer::handle(AbstractExamPaper* abstractPaper) {
    ExamPaper* paper = getConcretePaper(abstractPaper, "AssistantLecturer");
    if (paper == nullptr) {
        return;
    }

    std::cout << "[AssistantLecturer] Mark questions "
              << paper->getTutorQuestionCount() + 1 << "-"
              << paper->getQuestionCount() << " for "
              << paper->getModuleCode() << "." << std::endl;
    double awardedMarks;
    if (!readMarks("[AssistantLecturer] Enter subtotal",
                   paper->getAssistantLecturerMaximumMarks(), awardedMarks)) {
        return;
    }
    if (!paper->setAssistantLecturerMarks(awardedMarks)) {
        std::cerr << "[AssistantLecturer] The subtotal is outside the assigned mark range."
                  << std::endl;
        return;
    }
    if (!captureEscalationFlags(paper, "AssistantLecturer")) {
        return;
    }

    if (paper->hasPendingEscalation() && !forwardToNext(paper)) {
        std::cerr << "[AssistantLecturer] Escalation flags are set, but no Lecturer is "
                     "configured."
                  << std::endl;
    }
}

void AssistantLecturer::update() {

    if (paper == nullptr) {
        return;
    }

    std::cout << "[AssistantLecturer] Notified that an exam paper is ready for marking."
              << std::endl;
}

Lecturer::Lecturer(std::string id, std::string name) : Marker(id, name) {}

void Lecturer::handle(AbstractExamPaper* abstractPaper) {
    ExamPaper* paper = getConcretePaper(abstractPaper, "Lecturer");
    if (paper == nullptr) {
        return;
    }
    if (!paper->hasPendingEscalation()) {
        std::cerr << "[Lecturer] No pending escalation exists for this paper." << std::endl;
        return;
    }

    std::cout << "[Lecturer] Reviewing escalated paper "
              << paper->getModuleCode() << ". Flags:"
              << (paper->hasPhysicalError() ? " physical-error" : "")
              << (paper->hasMarkDiscrepancy() ? " mark-discrepancy" : "")
              << (paper->hasManualEscalation() ? " manual-escalation" : "")
              << std::endl;

    double finalMarks;
    if (!readMarks("[Lecturer] Enter replacement final score",
                   paper->getMaximumMarks(), finalMarks)) {
        return;
    }
    if (!paper->resolveEscalation(finalMarks)) {
        std::cerr << "[Lecturer] Could not resolve the escalation with that score."
                  << std::endl;
        return;
    }
    std::cout << "[Lecturer] Final score recorded: " << paper->getMarks() << "/"
              << paper->getMaximumMarks() << "." << std::endl;
}

void Lecturer::update() {
    
    if (paper == nullptr) {
        return;
    }

    std::cout << "[Lecturer] Notified that an exam paper requires review." << std::endl;
}
