#ifndef ConcreteHandler2_h
#define ConcreteHandler2_h

#include "TaskEscalationManager.h"

class ConcreteHandler2 : public TaskEscalationManager {
    
public:
    virtual void handleRequest() override;
};

#endif
