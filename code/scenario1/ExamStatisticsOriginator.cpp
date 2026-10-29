#include "ExamStatisticsOriginator.h"
#include "StatisticsMemento.h"
#include <iostream>

ExamStatisticsOriginator::ExamStatisticsOriginator(int y, double pass, double avg, double dist, double fail) : year(y), passRate(pass), averageMark(avg), distinctionRate(dist), failureRate(fail) {}

StatisticsMemento* ExamStatisticsOriginator::createMemento() {
    
    std::cout << "[ExamStatisticsOriginator] Creating snapshot memento for year " << year << std::endl;
    return new StatisticsMemento(year, passRate, averageMark, distinctionRate, failureRate);
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

    std::cout << "[ExamStatisticsOriginator] Restored statistics from memento (Year: " << year << ")" << std::endl;
}

