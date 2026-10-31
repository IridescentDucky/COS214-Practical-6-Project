#ifndef EXAMSTATSSTRATEGY_H
#define EXAMSTATSSTRATEGY_H

class ExamPaperCollection;
class ExamStatisticsOriginator;

class ExamStatsStrategy
{
public:
    virtual ~ExamStatsStrategy()
    {
    }

    virtual double calculateStat(ExamPaperCollection* papers, ExamStatisticsOriginator* statistics) = 0;
};

#endif
