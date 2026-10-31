#include "ConcreteStrategyA.h"
#include <iostream>

// concreteStrategyA does an average algorithm

template <typename T>
double ConcreteStrategyA<T>::algorithm(AbstractWorkItem<T>* workItem) {
    
    if (workItem == nullptr) {
        std::cout << "[Strategy A] workItem is null." << std::endl;
        return 0.0;
    }

    int count = workItem->getTaskCount();
    if (count == 0) {
        std::cout << "[Strategy A] No tasks to average." << std::endl;
        return 0.0;
    }

    int totalScore = 0;
    for (int i = 0; i < count; ++i) {
        const TaskRecord& task = workItem->getTask(i);
        totalScore += task.score;
    }

    double average = static_cast<double>(totalScore) / count;
    std::cout << "[Strategy A] Calculated overall average score: " << average << std::endl;
    return average;
}

template class ConcreteStrategyA<int>;
