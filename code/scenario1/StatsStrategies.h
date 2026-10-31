#ifndef STATSSTRATEGIES_H
#define STATSSTRATEGIES_H

#include "ExamStatsStrategy.h"

class AverageMarksStrategy : public ExamStatsStrategy
{
public:
    double calculateStat(ExamPaperCollection* papers, ExamStatisticsOriginator* statistics) override;
};

class TopMarkStrategy : public ExamStatsStrategy
{
public:
    double calculateStat(ExamPaperCollection* papers, ExamStatisticsOriginator* statistics) override;
};

#endif
