#include "TIVIDY.h"

#include <iostream>

int main()
{
    TIVIDY tividy;

    std::cout << "--- Happy path ---" << std::endl;
    int a = tividy.createWorkItem("Task A", 5);
    tividy.advanceWork(a);
    tividy.advanceWork(a);
    tividy.pauseWork(a);
    tividy.resumeWork(a);
    tividy.submitWork(a, "result");
    tividy.advanceWork(a);
    tividy.advanceWork(a);
    tividy.advanceWork(a);

    std::cout << "--- Invalid operations ---" << std::endl;
    int b = tividy.createWorkItem("Task B", 5);
    tividy.pauseWork(b);
    tividy.resumeWork(b);
    tividy.pauseWork(99);

    std::cout << "--- Rework ---" << std::endl;
    tividy.advanceWork(b);
    tividy.advanceWork(b);
    tividy.submitWork(b, "");
    tividy.advanceWork(b);
    tividy.submitWork(b, "fixed result");
    tividy.advanceWork(b);

    std::cout << "--- Status ---" << std::endl;
    tividy.printStatus();

    return 0;
}
