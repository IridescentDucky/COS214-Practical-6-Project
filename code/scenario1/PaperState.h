#ifndef PAPERSTATE_h
#define PAPERSTATE_h

class PaperState{
    
public:
    virtual ~PaperState() = default;
    
    virtual void write() = 0;
    virtual void deliver() = 0;
    virtual void startMarking() = 0;
    virtual void pause() = 0;
    virtual void completeMarking() = 0;
    virtual void captureMarks() = 0;
    virtual void archive() = 0;
    virtual void marked() = 0;
    virtual void createException() = 0;
    virtual void fail() = 0;
    virtual void validate() = 0;
    virtual void resumeMarking() = 0;
};

#endif
