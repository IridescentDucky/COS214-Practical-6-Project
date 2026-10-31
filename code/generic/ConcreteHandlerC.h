#ifndef ConcreteHandlerC_h
#define ConcreteHandlerC_h

#include "TaskEscalationManager.h"

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class ConcreteHandlerC : public TaskEscalationManager<T> {
private:
    string name;
public:
    ConcreteHandlerC(string name, T condition);
    void handleRequest(T a);

    void update();//for observer

    ~ConcreteHandlerC() override = default;
};

#endif
