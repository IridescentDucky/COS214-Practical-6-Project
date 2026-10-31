#include "ExamStatisticsOriginator.h"
#include "StatisticsMemento.h"
#include "ExamStatsStrategy.h"
#include "ExamPaperCollection.h"
#include <iostream>

ExamStatisticsOriginator::ExamStatisticsOriginator()
    : year(0),
      passRate(0.0),
      averageMark(0.0),
      maxMark(0.0),
      distinctionRate(0.0),
      failureRate(0.0),
      strategy(nullptr) {}

ExamStatisticsOriginator::ExamStatisticsOriginator(
    int y, double avg, double max, double dist, double fail)
    : year(y),
      passRate(0.0),
      averageMark(avg),
      maxMark(max),
      distinctionRate(dist),
      failureRate(fail),
      strategy(nullptr) {}

void ExamStatisticsOriginator::setStrategy(ExamStatsStrategy* strategy) {
    this->strategy = strategy;
}

double ExamStatisticsOriginator::calculate(ExamPaperCollection* papers) {
    
    if (strategy == nullptr || papers == nullptr) {
        std::cout << "[ExamStatisticsOriginator] Set a strategy and papers before calculating." << std::endl;
        return 0.0;
    }
    return strategy->calculateStat(papers, this);
}

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
    maxMark = 0.0;
    distinctionRate = requestedDistinctionRate;
    failureRate = requestedFailureRate;
    paperMetrics = requestedPaperMetrics;
}

void ExamStatisticsOriginator::setAverageMark(double average) {
    this->averageMark = average;
}

void ExamStatisticsOriginator::setMaxMark(double max) {
    this->maxMark = max;
}

double ExamStatisticsOriginator::getAverageMark() const {
    return averageMark;
}

double ExamStatisticsOriginator::getMaxMark() const {
    return maxMark;
}

StatisticsMemento* ExamStatisticsOriginator::createMemento() {
    
    std::cout << "[ExamStatisticsOriginator] Creating snapshot memento for year " << year << std::endl;
    return new StatisticsMemento(
        year, passRate, averageMark, maxMark, distinctionRate, failureRate, paperMetrics);
}

void ExamStatisticsOriginator::restoreMemento(StatisticsMemento* memento) {
    
    if (memento == nullptr) {
        
        std::cout << "[ExamStatisticsOriginator] Cannot restore from a null memento." << std::endl;
        return;
    }

    this->year = memento->getYear();
    this->passRate = memento->getPassRate();
    this->averageMark = memento->getAverageMark();
    this->maxMark = memento->getMaxMark();
    this->distinctionRate = memento->getDistinctionRate();
    this->failureRate = memento->getFailureRate();
    this->paperMetrics = memento->getPaperMetrics();

    std::cout << "[ExamStatisticsOriginator] Restored statistics from memento (Year: " << year << ", average: " << averageMark << ", top: " << maxMark << ")" << std::endl;
}
