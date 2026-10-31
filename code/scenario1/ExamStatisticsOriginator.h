#ifndef EXAMSTATISTICSORIGINATOR_H
#define EXAMSTATISTICSORIGINATOR_H

#include "ExamResultsStrategy.h"

#include <vector>

class StatisticsMemento;

class ExamStatisticsOriginator {
private:
    int year;
    double passRate;
    double averageMark;
    double distinctionRate;
    double failureRate;
    std::vector<ExamMetricResult> paperMetrics;
    
public:
    ExamStatisticsOriginator();
    void setStatistics(
        int year,
        double passRate,
        double averageMark,
        double distinctionRate,
        double failureRate,
        const std::vector<ExamMetricResult>& paperMetrics);
    StatisticsMemento* createMemento();
    void restoreMemento(StatisticsMemento* memento);
};

#endif
