#ifndef STATES_h
#define STATES_h

#include "PaperState.h"

//----------- WrittenState ---------------------------------------

class WrittenState :public PaperState{
public:
    explicit WrittenState(AbstractExamPaper* paper) : PaperState(paper) {}
    void nextState() override;
};

//----------- DeliveredState -------------------------------------

class DeliveredState :public PaperState{
public:
    explicit DeliveredState(AbstractExamPaper* paper) : PaperState(paper) {}
    void nextState() override;
};

//----------- MarkingState ---------------------------------------

class MarkingState :public PaperState{
public:
    explicit MarkingState(AbstractExamPaper* paper) : PaperState(paper) {}
    void pause() override;
    void completeMarking() override;
    void nextState() override;
    void createException() override;
    void validate() override;
    void fail() override;
};

//----------- ExceptionState -------------------------------------

class ExceptionState :public PaperState{
public:
    explicit ExceptionState(AbstractExamPaper* paper) : PaperState(paper) {}
    void pause() override;
};

//----------- PausedState ----------------------------------------

class PausedState :public PaperState{
public:
    explicit PausedState(AbstractExamPaper* paper) : PaperState(paper) {}
    void resumeMarking() override;
};

//----------- ValidatedState -------------------------------------

class ValidatedState :public PaperState{
public:
    explicit ValidatedState(AbstractExamPaper* paper) : PaperState(paper) {}
    void nextState() override;
};

//----------- MarkedState ----------------------------------------

class MarkedState :public PaperState{
public:
    explicit MarkedState(AbstractExamPaper* paper) : PaperState(paper) {}
    void nextState() override;
};

//----------- CapturedState --------------------------------------

class CapturedState :public PaperState{
public:
    explicit CapturedState(AbstractExamPaper* paper) : PaperState(paper) {}
    void nextState() override;
};

//----------- FailedState ----------------------------------------

class FailedState :public PaperState{
public:
    explicit FailedState(AbstractExamPaper* paper) : PaperState(paper) {}
    void pause() override;
};

//----------- end. -----------------------------------------------

#endif
