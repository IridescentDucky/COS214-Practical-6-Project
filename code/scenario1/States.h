#ifndef STATES_h
#define STATES_h

#include "PaperState.h"

//----------- WrittenState ---------------------------------------

class WrittenState :public PaperState{
    
public:
    void deliver();
};

//----------- DeliveredState -------------------------------------

class DeliveredState :public PaperState{
    
public:
    void startMarking();
};

//----------- MarkingState ---------------------------------------

class MarkingState :public PaperState{
    
public:
    void pause();
    void completeMarking();
    void createException();
    void validate();
    void fail();
};

//----------- ExceptionState -------------------------------------

class ExceptionState :public PaperState{
    
public:
    void pause();
};

//----------- PausedState ----------------------------------------

class PausedState :public PaperState{
    
public:
    void resumeMarking();
};

//----------- ValidatedState -------------------------------------

class ValidatedState :public PaperState{
    
public:
    void marked();
};

//----------- MarkedState ----------------------------------------

class MarkedState :public PaperState{
    
public:
    void captureMarks();
};

//----------- CapturedState --------------------------------------

class CapturedState :public PaperState{
    
public:
    void archive();
};

//----------- FailedState ----------------------------------------

class FailedState :public PaperState{
    
public:
    void pause();
};

//----------- end. -----------------------------------------------

#endif
