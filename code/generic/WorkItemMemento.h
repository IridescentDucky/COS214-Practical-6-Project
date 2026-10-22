#ifndef WORKITEMMEMENTO_H
#define WORKITEMMEMENTO_H

class WorkItemState;

class WorkItemMemento{
    
private:
    WorkItemState* state;
    
public:
    WorkItemMemento(WorkItemState* s);
    ~WorkItemMemento();
    // Returns a newly allocated copy. The caller owns the returned state.
    WorkItemState* getState() const;
    void setState(WorkItemState* s);
};

#endif
