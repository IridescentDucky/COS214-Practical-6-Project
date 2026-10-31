#ifndef ConcreteHandler_h
#define ConcreteHandler_h

#include "TaskEscalationManager.h"

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class ConcreteHandler : public TaskEscalationManager<T> {
private:
    string name;
public:
    ConcreteHandler(string name, T condition);
    void handleRequest(T a);

    void update();//for observer

    ~ConcreteHandler() override = default;
};

#endif
