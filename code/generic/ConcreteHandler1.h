#ifndef ConcreteHandler1_h
#define ConcreteHandler1_h

#include "TaskEscalationManager.h"

class ConcreteHandler1 : public TaskEscalationManager {
    
public:
    ConcreteHandler1() = default;
    ~ConcreteHandler1() override = default;
    virtual void handleRequest() override;
};

#endif
