#include "ExamMarkingFacade.h"
#include "StatsStrategies.h"

#include <iostream>

int main()
{
    ExamMarkingFacade facade(2026);

    std::cout << "=== 1. Create papers (Facade + Factory Method) ===" << std::endl;
    int cos214 = facade.createExamPaper("COS214", 120);
    facade.addQuestion(cos214, "Explain the Observer pattern", 10);
    facade.addQuestion(cos214, "Draw a class diagram", 20);
    facade.addQuestion(cos214, "Implement a Strategy", 20);
    int cos212 = facade.createExamPaper("COS212", 90);
    facade.addQuestion(cos212, "Insert into a binary search tree", 25);
    facade.addQuestion(cos212, "Analyse heap sort", 25);

    std::cout << std::endl << "=== 2. Mark papers (Chain of Responsibility) ===" << std::endl;
    facade.captureMarks(cos214);
    facade.captureMarks(cos212);

    std::cout << std::endl << "=== 3. Statistics (Strategy + Iterator + Memento) ===" << std::endl;
    AverageMarksStrategy average;
    TopMarkStrategy top;
    facade.generateStatistics(&average);
    facade.generateStatistics(&top);
    facade.undoStatistics();

    return 0;
}
