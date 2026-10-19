#ifndef TaskEscalationManager_h
#define TaskEscalationManager_h

class TaskEscalationManager {
    
protected:
    TaskEscalationManager* successor = nullptr;
    
public:
    virtual ~TaskEscalationManager() = default;
    virtual void handleRequest() = 0;
    void setSuccessor(TaskEscalationManager* next){
        this->successor = next;
    }
    
};

#endif
