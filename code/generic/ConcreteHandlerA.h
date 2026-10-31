#ifndef ConcreteHandlerA_h
#define ConcreteHandlerA_h

#include "TaskEscalationManager.h"

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class ConcreteHandlerA : public TaskEscalationManager<T> {
private:
    string name;
public:
    ConcreteHandlerA(string name, T condition);
    void handleRequest(T a);

    void update();//for observer

    ~ConcreteHandlerA() override = default;
};

#endif
