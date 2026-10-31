#include "ExamMarkingFacade.h"

#include "ExamPaper.h"
#include "ExamStatsStrategy.h"
#include "Marker.h"
#include "AverageMarksStrategy.h"
#include "LowestMarkStrategy.h"
#include "StatisticsMemento.h"
#include "TopMarkStrategy.h"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>

ExamMarkingFacade::ExamMarkingFacade() : ExamMarkingFacade(0) {}

ExamMarkingFacade::ExamMarkingFacade(int year)
    : year(year),
      tutor("T1", "Tutor"),
      assistantLecturer("AL1", "Assistant Lecturer"),
      lecturer("L1", "Lecturer"),
      statistics(year, 0.0, 0.0, 0.0, 0.0) {
    tutor.setNext(&assistantLecturer);
    assistantLecturer.setNext(&lecturer);
}

ExamMarkingFacade::~ExamMarkingFacade() = default;

ExamPaper* ExamMarkingFacade::find(int paperIndex) const {
    ExamPaper* paper = dynamic_cast<ExamPaper*>(papers.getPaperAt(paperIndex));
    if (paper == nullptr) {
        std::cout << "[ExamMarkingFacade] No exam paper at index " << paperIndex
                  << std::endl;
    }
    return paper;
}

bool ExamMarkingFacade::ownsPaper(const ExamPaper* paper) const {
    for (int index = 0; index < papers.getSize(); ++index) {
        if (papers.getPaperAt(index) == paper) {
            return true;
        }
    }
    return false;
}

int ExamMarkingFacade::createExamPaper(
    const std::string& moduleCode,
    int duration) {
    createExamPaper(moduleCode, duration, 0.0, year);
    return papers.getSize() - 1;
}

ExamPaper* ExamMarkingFacade::createExamPaper(
    const std::string& moduleCode,
    int examDuration,
    double initialMarks,
    int paperYear) {
    std::unique_ptr<AbstractExamPaper> created(
        creator.createExamPaper(moduleCode, examDuration, initialMarks, paperYear));
    ExamPaper* paper = dynamic_cast<ExamPaper*>(created.get());
    if (paper == nullptr) {
        throw std::logic_error("ExamPaperCreator returned an unsupported paper type.");
    }

    std::unique_ptr<ExamPaper> owned(static_cast<ExamPaper*>(created.release()));
    ownedPapers.push_back(std::move(owned));
    papers.addPaper(paper);
    return paper;
}

bool ExamMarkingFacade::addQuestion(
    int paperIndex,
    const std::string& question,
    double maximumMarks) {
    ExamPaper* paper = find(paperIndex);
    if (paper == nullptr) {
        return false;
    }
    paper->addQuestion(question, maximumMarks);
    return true;
}

bool ExamMarkingFacade::captureMarks(int paperIndex) {
    ExamPaper* paper = find(paperIndex);
    if (paper == nullptr) {
        return false;
    }
    paper->setMarker(&tutor);
    paper->mark();
    std::cout << "[ExamMarkingFacade] " << paper->getModuleCode()
              << " final mark: " << paper->getMarks() << "/"
              << paper->getMaximumMarks() << std::endl;
    return true;
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

ExamMetricResult ExamMarkingFacade::calculateMetric(
    const ExamPaper* paper,
    ExamMetric metric) const {
    ExamMetricResult invalidResult;
    invalidResult.metric = metric;
    invalidResult.metricName = getExamMetricName(metric);
    if (paper == nullptr || !ownsPaper(paper)) {
        std::cerr << "[ExamMarkingFacade] Cannot calculate a metric for a paper not "
                     "owned by this facade."
                  << std::endl;
        return invalidResult;
    }
    invalidResult.moduleCode = paper->getModuleCode();
    if (!paper->isMarked() || paper->hasPendingEscalation()) {
        std::cerr << "[ExamMarkingFacade] Cannot calculate a metric for an incomplete "
                     "or unresolved paper."
                  << std::endl;
        return invalidResult;
    }

    switch (metric) {
    case ExamMetric::TopQuestion: {
        TopMarkStrategy strategy;
        return strategy.calculateStats(*paper);
    }
    case ExamMetric::LowestQuestion: {
        LowestMarkStrategy strategy;
        return strategy.calculateStats(*paper);
    }
    case ExamMetric::MarksPerAllocatedMinute: {
        AverageMarksStrategy strategy;
        return strategy.calculateStats(*paper);
    }
    }

    std::cerr << "[ExamMarkingFacade] Unsupported exam metric." << std::endl;
    return invalidResult;
}

double ExamMarkingFacade::generateStatistics(ExamStatsStrategy* strategy) {
    if (strategy == nullptr) {
        std::cout << "[ExamMarkingFacade] Choose a statistics strategy first."
                  << std::endl;
        return 0.0;
    }
    history.saveMemento(statistics.createMemento());
    statistics.setStrategy(strategy);
    return statistics.calculate(&papers);
}

const StatisticsMemento* ExamMarkingFacade::generateStatistics(int requestedYear) {
    std::size_t paperCount = 0;
    std::size_t passCount = 0;
    std::size_t distinctionCount = 0;
    std::size_t failureCount = 0;
    double percentageTotal = 0.0;
    std::vector<ExamMetricResult> paperMetrics;

    for (int index = 0; index < papers.getSize(); ++index) {
        ExamPaper* paper = dynamic_cast<ExamPaper*>(papers.getPaperAt(index));
        if (paper == nullptr || paper->getYear() != requestedYear ||
            !paper->isMarked() || paper->hasPendingEscalation()) {
            continue;
        }

        const double maximumMarks = paper->getMaximumMarks();
        if (maximumMarks <= 0.0) {
            std::cerr << "[ExamMarkingFacade] Skipping a marked paper with no maximum "
                         "marks."
                      << std::endl;
            continue;
        }

        const double percentage = paper->getMarks() / maximumMarks * 100.0;
        ++paperCount;
        percentageTotal += percentage;
        if (percentage < 50.0) {
            ++failureCount;
        } else if (percentage < 75.0) {
            ++passCount;
        } else {
            ++distinctionCount;
        }

        paperMetrics.push_back(calculateMetric(paper, ExamMetric::TopQuestion));
        paperMetrics.push_back(calculateMetric(paper, ExamMetric::LowestQuestion));
        paperMetrics.push_back(
            calculateMetric(paper, ExamMetric::MarksPerAllocatedMinute));
    }

    if (paperCount == 0) {
        std::cerr << "[ExamMarkingFacade] No resolved, marked papers are available for "
                     "statistics in year "
                  << requestedYear << "." << std::endl;
        return nullptr;
    }

    const double denominator = static_cast<double>(paperCount);
    statistics.setStatistics(
        requestedYear,
        static_cast<double>(passCount) / denominator * 100.0,
        percentageTotal / denominator,
        static_cast<double>(distinctionCount) / denominator * 100.0,
        static_cast<double>(failureCount) / denominator * 100.0,
        paperMetrics);

    std::unique_ptr<StatisticsMemento> snapshot(statistics.createMemento());
    history.saveMemento(snapshot.get());
    snapshot.release();
    return history.getMemento();
}

void ExamMarkingFacade::undoStatistics() {
    statistics.restoreMemento(history.getMemento());
}
