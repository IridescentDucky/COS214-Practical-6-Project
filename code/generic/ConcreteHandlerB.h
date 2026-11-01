#ifndef ConcreteHandlerB_h
#define ConcreteHandlerB_h

#include "TaskEscalationManager.h"

#include <iostream>
#include <string>

using namespace std;

/** @brief Escalation handler for the second configured responsibility level. */
template <typename T>
class ConcreteHandlerB : public TaskEscalationManager<T> {
private:
    string name;
public:
    /** @brief Creates a handler with a name and escalation threshold.
     *  @param name Name of the responsible level.
     *  @param condition Threshold handled by this level.
     */
    ConcreteHandlerB(string name, T condition);
    /** @brief Handles an escalation request or passes it onward. */
    void handleRequest(T a);

    /** @brief Updates the handler in response to its work item. */
    void update();//for observer

    /** @brief Destroys the handler. */
    ~ConcreteHandlerB() override = default;
};

#endif
