#ifndef TOPMARKSTRATEGY_H
#define TOPMARKSTRATEGY_H

#include "ExamResultsStrategy.h"

class TopMarkStrategy : public ExamResultsStrategy {
public:
    ExamMetricResult calculateStats(const ExamPaper& paper) const override;
};

#endif
