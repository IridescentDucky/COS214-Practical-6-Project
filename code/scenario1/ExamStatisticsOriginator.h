#ifndef EXAMSTATISTICSORIGINATOR_H
#define EXAMSTATISTICSORIGINATOR_H

#include "ExamResultsStrategy.h"

#include <vector>

class StatisticsMemento;
class ExamStatsStrategy;
class ExamPaperCollection;

class ExamStatisticsOriginator {
private:
    int year;
    double passRate;
    double averageMark;
    double maxMark;
    double distinctionRate;
    double failureRate;
    ExamStatsStrategy* strategy;
    std::vector<ExamMetricResult> paperMetrics;

public:
    ExamStatisticsOriginator();
    ExamStatisticsOriginator(int y, double avg, double max, double dist, double fail);
    void setStrategy(ExamStatsStrategy* strategy);
    double calculate(ExamPaperCollection* papers);
    void setStatistics(
        int year,
        double passRate,
        double averageMark,
        double distinctionRate,
        double failureRate,
        const std::vector<ExamMetricResult>& paperMetrics);
    void setAverageMark(double average);
    void setMaxMark(double max);
    double getAverageMark() const;
    double getMaxMark() const;
    StatisticsMemento* createMemento();
    void restoreMemento(StatisticsMemento* memento);
};

#endif
