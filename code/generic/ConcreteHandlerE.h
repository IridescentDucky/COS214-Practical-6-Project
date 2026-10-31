#ifndef ConcreteHandlerE_h
#define ConcreteHandlerE_h

#include "TaskEscalationManager.h"

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class ConcreteHandlerE : public TaskEscalationManager<T> {
private:
    string name;
public:
    ConcreteHandlerE(string name, T condition);
    void handleRequest(T a);

    void update();//for observer

    ~ConcreteHandlerE() override = default;
};

#endif
