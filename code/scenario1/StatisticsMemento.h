#ifndef STATISTICSMEMENTO_H
#define STATISTICSMEMENTO_H

#include "ExamResultsStrategy.h"

#include <vector>

class StatisticsMemento {
private:
    int year;
    double passRate;
    double averageMark;
    double distinctionRate;
    double failureRate;
    std::vector<ExamMetricResult> paperMetrics;
    
public:
    StatisticsMemento(
        int y,
        double pass,
        double avg,
        double dist,
        double fail,
        const std::vector<ExamMetricResult>& metrics)
        : year(y),
          passRate(pass),
          averageMark(avg),
          distinctionRate(dist),
          failureRate(fail),
          paperMetrics(metrics) {}

    int getYear() const { return year; }
    double getPassRate() const { return passRate; }
    double getAverageMark() const { return averageMark; }
    double getDistinctionRate() const { return distinctionRate; }
    double getFailureRate() const { return failureRate; }
    const std::vector<ExamMetricResult>& getPaperMetrics() const { return paperMetrics; }
};

#endif
