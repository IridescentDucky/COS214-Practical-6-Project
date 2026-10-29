#ifndef STATISTICSMEMENTO_H
#define STATISTICSMEMENTO_H

class StatisticsMemento{
    
private:
    int year;
    double passRate;
    double averageMark;
    double distinctionRate;
    double failureRate;
    
public:
    StatisticsMemento(int y, double pass, double avg, double dist, double fail): year(y), passRate(pass), averageMark(avg), distinctionRate(dist), failureRate(fail) {}

    int getYear() const { return year; }
    double getPassRate() const { return passRate; }
    double getAverageMark() const { return averageMark; }
    double getDistinctionRate() const { return distinctionRate; }
    double getFailureRate() const { return failureRate; }
};

#endif
