#include "StatsStrategies.h"
#include "ExamPaper.h"
#include "ExamPaperCollection.h"
#include "ExamStatisticsOriginator.h"
#include "Iterator.h"

#include <iostream>

double LegacyStatistics::AverageMarksStrategy::calculateStat(
    ExamPaperCollection* papers,
    ExamStatisticsOriginator* statistics)
{
    double total = 0.0;
    int count = 0;
    Iterator* it = papers->createIterator();
    while (it->hasNext())
    {
        total += it->next()->getMarks();
        ++count;
    }
    delete it;

    double average = count > 0 ? total / count : 0.0;
    statistics->setAverageMark(average);
    std::cout << "[AverageMarksStrategy] Average mark over " << count << " paper(s): " << average << std::endl;
    return average;
}

double LegacyStatistics::TopMarkStrategy::calculateStat(
    ExamPaperCollection* papers,
    ExamStatisticsOriginator* statistics)
{
    double top = 0.0;
    Iterator* it = papers->createIterator();
    while (it->hasNext())
    {
        double marks = it->next()->getMarks();
        if (marks > top)
        {
            top = marks;
        }
    }
    delete it;

    statistics->setMaxMark(top);
    std::cout << "[TopMarkStrategy] Top mark: " << top << std::endl;
    return top;
}
