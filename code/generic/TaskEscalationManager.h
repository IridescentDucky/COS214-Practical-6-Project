#ifndef TaskEscalationManager_h
#define TaskEscalationManager_h

template <typename T>
class AbstractWorkItem;

template <typename T>
class TaskEscalationManager {
protected:
    TaskEscalationManager<T>* successor = nullptr;
    T condition;
    AbstractWorkItem<T>* workItem = nullptr;   //for observer cause we need to pull the state
    
public:
    TaskEscalationManager(T condition) : condition(condition) {}

    virtual void handleRequest(T a) = 0;
    void setSuccessor(TaskEscalationManager<T>* next);

    virtual ~TaskEscalationManager();

    virtual void update() = 0;//for observer
};

#endif
