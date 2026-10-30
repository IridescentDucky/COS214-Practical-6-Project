#include "ConcreteStrategyC.h"
#include <iostream>

// concreteStrategyC gets the min score

template <typename T>
double ConcreteStrategyC<T>::algorithm(AbstractWorkItem<T>* workItem) {
    
    if (workItem == nullptr) {
        std::cout << "[Strategy C] workItem is null." << std::endl;
        return 0.0;
    }

    int count = workItem->getTaskCount();
    if (count == 0) {
        std::cout << "[Strategy C] No tasks to evaluate." << std::endl;
        return 0.0;
    }

    // start with first task as the lowest score
    int lowestScore = workItem->getTask(0).score;
    
    for (int i = 1; i < count; ++i) {
        const TaskRecord& task = workItem->getTask(i);
        if (task.score < lowestScore) {
            lowestScore = task.score;
        }
    }

    std::cout << "[Strategy C] Calculated min score: " << lowestScore << std::endl;
    return static_cast<double>(lowestScore);
}

template class ConcreteStrategyC<int>;
