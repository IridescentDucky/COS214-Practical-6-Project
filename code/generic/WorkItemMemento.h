#ifndef WORKITEMMEMENTO_H
#define WORKITEMMEMENTO_H

class WorkItemState;

class WorkItemMemento{
    
private:
    WorkItemState* state;
    
public:
    WorkItemMemento(WorkItemState* s);
    ~WorkItemMemento() = default;
    WorkItemState* getState() const;
    void setState(WorkItemState* s);
};

#endif
