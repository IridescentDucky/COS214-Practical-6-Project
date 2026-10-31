#ifndef STATSMEMENTO_H
#define STATSMEMENTO_H

class StatsMemento {
    
private:
    int year;
    double maxMark;
    double minMark;
    double scoreAvg;
    
public:
    StatsMemento(int y, double max, double min, double sAvg): year(y), maxMark(max), minMark(min), scoreAvg(sAvg) {}
    
    int getYear() const { return year; }
    double getMaxMark() const { return maxMark; }
    double getMinMark() const { return minMark; }
    double getScoreAvg() const { return scoreAvg;}
};

#endif
