#ifndef PAPERSTATE_h
#define PAPERSTATE_h

class AbstractExamPaper;

class PaperState{
protected:
    AbstractExamPaper* paper;

    explicit PaperState(AbstractExamPaper* paper) : paper(paper) {}

public:
    virtual ~PaperState() = 0;

    virtual void nextState() {}
    virtual void pause() {}
    virtual void completeMarking() {}
    virtual void createException() {}
    virtual void fail() {}
    virtual void validate() {}
    virtual void resumeMarking() {}
};

#endif
