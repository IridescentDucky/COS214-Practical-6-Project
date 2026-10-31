#include "ExamMarkingFacade.h"

#include "ExamPaper.h"
#include "Marker.h"

#include <iostream>
#include <stdexcept>
#include <utility>

ExamMarkingFacade::~ExamMarkingFacade() = default;

bool ExamMarkingFacade::ownsPaper(const ExamPaper* paper) const {
    for (int index = 0; index < papers.getSize(); ++index) {
        if (papers.getPaperAt(index) == paper) {
            return true;
        }
    }
    return false;
}

ExamPaper* ExamMarkingFacade::createExamPaper(
    const std::string& moduleCode,
    int examDuration,
    double initialMarks,
    int year) {
    std::unique_ptr<AbstractExamPaper> created(
        creator.createExamPaper(moduleCode, examDuration, initialMarks, year));
    ExamPaper* paper = dynamic_cast<ExamPaper*>(created.get());
    if (paper == nullptr) {
        throw std::logic_error("ExamPaperCreator returned an unsupported paper type.");
    }

    std::unique_ptr<ExamPaper> owned(static_cast<ExamPaper*>(created.release()));
    ownedPapers.push_back(std::move(owned));
    papers.addPaper(paper);
    return paper;
}

void ExamMarkingFacade::assignPaper(ExamPaper* paper, Marker* chainHead) {
    if (!ownsPaper(paper)) {
        std::cerr << "[ExamMarkingFacade] Cannot assign a paper not owned by this facade."
                  << std::endl;
        return;
    }
    if (chainHead == nullptr) {
        std::cerr << "[ExamMarkingFacade] Cannot assign a null marker chain head."
                  << std::endl;
        return;
    }

    paper->setMarker(chainHead);
}

void ExamMarkingFacade::captureMarks(ExamPaper* paper) {
    if (!ownsPaper(paper)) {
        std::cerr << "[ExamMarkingFacade] Cannot mark a paper not owned by this facade."
                  << std::endl;
        return;
    }

    paper->mark();
}

void ExamMarkingFacade::generateStatistics() {
    std::cerr << "[ExamMarkingFacade] Statistics remain unavailable until the "
                 "results strategy is defined."
              << std::endl;
}
