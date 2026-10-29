#ifndef WORKITEMMEMENTO_H
#define WORKITEMMEMENTO_H

template <typename T>
class WorkItemState;

template <typename T>
class WorkItemMemento {
private:
    WorkItemState<T>* state;
    
public:
    WorkItemMemento(WorkItemState<T>* s);
    ~WorkItemMemento();
    // Returns a newly allocated copy. The caller owns the returned state.
    WorkItemState<T>* getState() const;
    void setState(WorkItemState<T>* s);
};

#endif
