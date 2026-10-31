#include "ExamStatisticsOriginator.h"
#include "StatisticsMemento.h"
#include <iostream>

ExamStatisticsOriginator::ExamStatisticsOriginator()
    : year(0), passRate(0.0), averageMark(0.0), distinctionRate(0.0), failureRate(0.0) {}

void ExamStatisticsOriginator::setStatistics(
    int requestedYear,
    double requestedPassRate,
    double requestedAverageMark,
    double requestedDistinctionRate,
    double requestedFailureRate,
    const std::vector<ExamMetricResult>& requestedPaperMetrics) {
    year = requestedYear;
    passRate = requestedPassRate;
    averageMark = requestedAverageMark;
    distinctionRate = requestedDistinctionRate;
    failureRate = requestedFailureRate;
    paperMetrics = requestedPaperMetrics;
}

StatisticsMemento* ExamStatisticsOriginator::createMemento() {
    
    std::cout << "[ExamStatisticsOriginator] Creating snapshot memento for year " << year << std::endl;
    return new StatisticsMemento(
        year, passRate, averageMark, distinctionRate, failureRate, paperMetrics);
}

void ExamStatisticsOriginator::restoreMemento(StatisticsMemento* memento) {
    
    if (memento == nullptr) {
        
        std::cout << "[ExamStatisticsOriginator] Cannot restore from a null memento." << std::endl;
        return;
    }

    this->year = memento->getYear();
    this->passRate = memento->getPassRate();
    this->averageMark = memento->getAverageMark();
    this->distinctionRate = memento->getDistinctionRate();
    this->failureRate = memento->getFailureRate();
    this->paperMetrics = memento->getPaperMetrics();

    std::cout << "[ExamStatisticsOriginator] Restored statistics from memento (Year: " << year << ")" << std::endl;
}
