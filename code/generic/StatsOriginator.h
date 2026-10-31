#ifndef STATSORIGINATOR_H
#define STATSORIGINATOR_H

#include "StatsMemento.h"
#include "AbstractWorkItem.h"
#include "Strategy.h"

template <typename T>
class StatsOriginator {
    
private:
    int year;
    double maxMark;
    double minMark;
    double scoreAvg;

    Strategy<T>* strategyA;
    Strategy<T>* strategyB;
    Strategy<T>* strategyC;

public:
    StatsOriginator(int y = 0);
    ~StatsOriginator();

    void calculateStats(AbstractWorkItem<T>* workItem);
    StatsMemento* createMemento() const;
    void restoreFromMemento(StatsMemento* m);
    void printState() const;
};

#endif
