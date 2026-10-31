#ifndef ConcreteHandlerD_h
#define ConcreteHandlerD_h

#include "TaskEscalationManager.h"

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class ConcreteHandlerD : public TaskEscalationManager<T> {
private:
    string name;
public:
    ConcreteHandlerD(string name, T condition);
    void handleRequest(T a);

    void update();//for observer

    ~ConcreteHandlerD() override = default;
};

#endif
