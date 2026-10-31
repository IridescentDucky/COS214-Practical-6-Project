#ifndef STATISTICSMEMENTO_H
#define STATISTICSMEMENTO_H

class StatisticsMemento{
    
private:
    int year;
    double averageMark;
    double maxMark;
    double distinctionRate;
    double failureRate;
    
public:
    StatisticsMemento(int y, double avg, double max, double dist, double fail): year(y), averageMark(avg), maxMark(max), distinctionRate(dist), failureRate(fail) {}

    int getYear() const { return year; }
    double getAverageMark() const { return averageMark; }
    double getMaxMark() const { return maxMark; }
    double getDistinctionRate() const { return distinctionRate; }
    double getFailureRate() const { return failureRate; }
};

#endif
