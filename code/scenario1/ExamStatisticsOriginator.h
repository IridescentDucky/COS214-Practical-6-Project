#ifndef EXAMSTATISTICSORIGINATOR_H
#define EXAMSTATISTICSORIGINATOR_H

class StatisticsMemento;
class ExamStatsStrategy;
class ExamPaperCollection;

class ExamStatisticsOriginator{
    
private:
    int year;
    double averageMark;
    double maxMark;
    double distinctionRate;
    double failureRate;
    ExamStatsStrategy* strategy;
    
public:
    ExamStatisticsOriginator(int y, double avg, double max, double dist, double fail);
    void setStrategy(ExamStatsStrategy* strategy);
    double calculate(ExamPaperCollection* papers);
    void setAverageMark(double average);
    void setMaxMark(double max);
    double getAverageMark() const;
    double getMaxMark() const;
    StatisticsMemento* createMemento();
    void restoreMemento(StatisticsMemento* memento);
};

#endif
