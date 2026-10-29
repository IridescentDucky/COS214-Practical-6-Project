#ifndef TaskEscalationManager_h
#define TaskEscalationManager_h

template <typename T>
class TaskEscalationManager {
protected:
    TaskEscalationManager<T>* successor = nullptr;
    T condition;
    
public:
    TaskEscalationManager(T condition) : condition(condition) {}

    virtual void handleRequest(T a) = 0;
    void setSuccessor(TaskEscalationManager<T>* next);

    virtual ~TaskEscalationManager();
};

#endif
