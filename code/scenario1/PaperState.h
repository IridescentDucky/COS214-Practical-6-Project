#ifndef PAPERSTATE_h
#define PAPERSTATE_h

class PaperState{
    
public:
    virtual ~PaperState() = default;
    
    virtual void write();
    virtual void deliver();
    virtual void startMarking();
    virtual void pause();
    virtual void completeMarking();
    virtual void captureMarks();
    virtual void archive();
    virtual void marked();
    virtual void createException();
    virtual void fail();
    virtual void validate();
    virtual void resumeMarking();
};

#endif
