#include "ConcreteStrategyB.h"
#include <iostream>

// concreteStrategyB gets the max score

template <typename T>
double ConcreteStrategyB<T>::algorithm(AbstractWorkItem<T>* workItem) {
    
    if (workItem == nullptr) {
        std::cout << "[Strategy B] workItem is null." << std::endl;
        return 0.0;
    }

    int count = workItem->getTaskCount();
    if (count == 0) {
        std::cout << "[Strategy B] No tasks to evaluate." << std::endl;
        return 0.0;
    }

    // start with first task is the highest score ...
    int highestScore = workItem->getTask(0).score;
    for (int i = 1; i < count; ++i) {
        const TaskRecord& task = workItem->getTask(i);
        if (task.score > highestScore) {
            highestScore = task.score;
        }
    }

    std::cout << "[Strategy B] Calculated max score: " << highestScore << std::endl;
        return static_cast<double>(highestScore);
}

template class ConcreteStrategyB<int>;
