#include "StatsOriginator.h"
#include "ConcreteStrategyA.h"
#include "ConcreteStrategyB.h"
#include "ConcreteStrategyC.h"
#include <iostream>

template <typename T>
StatsOriginator<T>::StatsOriginator(int y): year(y), maxMark(0.0), minMark(0.0), scoreAvg(0.0) {
    
    strategyA = new ConcreteStrategyA<T>();
    strategyB = new ConcreteStrategyB<T>();
    strategyC = new ConcreteStrategyC<T>();
}

template <typename T>
StatsOriginator<T>::~StatsOriginator() {
    
    delete strategyA;
    delete strategyB;
    delete strategyC;
}

template <typename T>
void StatsOriginator<T>::calculateStats(AbstractWorkItem<T>* workItem) {
    
    if (workItem == nullptr) {
        
        std::cout << "[StatsOriginator] Can't calculate stats, WorkItem is null." << std::endl;
        return;
    }

    scoreAvg = strategyA->algorithm(workItem);
    maxMark = strategyB->algorithm(workItem);
    minMark = strategyC->algorithm(workItem);
    
    std::cout << "[StatsOriginator] Stats fully updated via Strategies A, B, and C." << std::endl;
}

template <typename T>
StatsMemento* StatsOriginator<T>::createMemento() const {
    
    std::cout << "[StatsOriginator] Creating Memento snapshot." << std::endl;
    return new StatsMemento(year, maxMark, minMark, scoreAvg);
}

template <typename T>
void StatsOriginator<T>::restoreFromMemento(StatsMemento* m) {
    
    if (m != nullptr) {
        
        year = m->getYear();
        maxMark = m->getMaxMark();
        minMark = m->getMinMark();
        scoreAvg = m->getScoreAvg();
        std::cout << "[StatsOriginator] Stats restored from Memento." << std::endl;
    }
    else {
        
        std::cout << "[StatsOriginator] Cannot restore from a null Memento." << std::endl;
    }
}

template <typename T>
void StatsOriginator<T>::printState() const {
    
    std::cout << "[StatsOriginator]: print state: " << std::endl;
    std::cout << "[Year]: " << year << " [Max]: " << maxMark << " [Min]: " << minMark << " [Avg]: " << scoreAvg << std::endl;
}

template class StatsOriginator<int>;
