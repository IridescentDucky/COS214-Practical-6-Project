#ifndef EXAMSTATISTICSORIGINATOR_H
#define EXAMSTATISTICSORIGINATOR_H

class StatisticsMemento;

class ExamStatisticsOriginator{
    
private:
    int year;
    double passRate;
    double averageMark;
    double distinctionRate;
    double failureRate;
    
public:
    ExamStatisticsOriginator(int y, double pass, double avg, double dist, double fail);
    StatisticsMemento* createMemento();
    void restoreMemento(StatisticsMemento* memento);
};

#endif
