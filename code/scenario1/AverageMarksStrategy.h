#ifndef AVERAGEMARKSSTRATEGY_H
#define AVERAGEMARKSSTRATEGY_H

#include "ExamResultsStrategy.h"

class AverageMarksStrategy : public ExamResultsStrategy {
public:
    ExamMetricResult calculateStats(const ExamPaper& paper) const override;
};

#endif
