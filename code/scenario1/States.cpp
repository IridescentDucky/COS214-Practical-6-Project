#include "PaperState.h"
#include "States.h"

//----------- WrittenState ---------------------------------------

void WrittenState::deliver(){
    
    return;
}

//----------- DeliveredState -------------------------------------

void DeliveredState::startMarking(){
    
    return;
}

//----------- MarkingState ---------------------------------------

void MarkingState::pause(){
    
    return;
}

void MarkingState::completeMarking(){
    
    return;
}

void MarkingState::createException(){
    
    return;
}

void MarkingState::validate(){
    
    return;
}

void MarkingState::fail(){
    
    return;
}

//----------- ExceptionState -------------------------------------

void ExceptionState::pause(){
    
    return;
}

//----------- PausedState ----------------------------------------

void PausedState::resumeMarking(){
    
    return;
}

//----------- ValidatedState -------------------------------------

void ValidatedState::marked(){
    
    return;
}

//----------- MarkedState ----------------------------------------

void MarkedState::captureMarks(){
    
    return;
}

//----------- CapturedState --------------------------------------

void CapturedState::archive(){
    
    return;
}

//----------- FailedState ----------------------------------------

void FailedState::pause(){
    
    return;
}

//----------- end. -----------------------------------------------
