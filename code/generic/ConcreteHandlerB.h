#ifndef ConcreteHandlerB_h
#define ConcreteHandlerB_h

#include "TaskEscalationManager.h"

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class ConcreteHandlerB : public TaskEscalationManager<T> {
private:
    string name;
public:
    ConcreteHandlerB(string name, T condition);
    void handleRequest(T a);

    void update();//for observer

    ~ConcreteHandlerB() override = default;
};

#endif
