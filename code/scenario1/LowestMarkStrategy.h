#ifndef LOWESTMARKSTRATEGY_H
#define LOWESTMARKSTRATEGY_H

#include "ExamResultsStrategy.h"

class LowestMarkStrategy : public ExamResultsStrategy {
public:
    ExamMetricResult calculateStats(const ExamPaper& paper) const override;
};

#endif
