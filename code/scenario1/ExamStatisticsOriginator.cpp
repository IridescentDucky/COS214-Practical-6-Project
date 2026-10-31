#include "ExamStatisticsOriginator.h"
#include "StatisticsMemento.h"
#include "ExamStatsStrategy.h"
#include <iostream>

ExamStatisticsOriginator::ExamStatisticsOriginator(int y, double avg, double max, double dist, double fail) : year(y), averageMark(avg), maxMark(max), distinctionRate(dist), failureRate(fail), strategy(nullptr) {}

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
    return new StatisticsMemento(year, averageMark, maxMark, distinctionRate, failureRate);
}

void ExamStatisticsOriginator::restoreMemento(StatisticsMemento* memento) {
    
    if (memento == nullptr) {
        
        std::cout << "[ExamStatisticsOriginator] Cannot restore from a null memento." << std::endl;
        return;
    }

    this->year = memento->getYear();
    this->averageMark = memento->getAverageMark();
    this->maxMark = memento->getMaxMark();
    this->distinctionRate = memento->getDistinctionRate();
    this->failureRate = memento->getFailureRate();

    std::cout << "[ExamStatisticsOriginator] Restored statistics from memento (Year: " << year << ", average: " << averageMark << ", top: " << maxMark << ")" << std::endl;
}

