#include "PaperState.h"
#include "States.h"

//----------- WrittenState ---------------------------------------

void WrittenState::deliver(){
    
}

//----------- DeliveredState -------------------------------------

void DeliveredState::startMarking(){
    
}

//----------- MarkingState ---------------------------------------

void MarkingState::pause(){
    
}

void MarkingState::completeMarking(){
    
}

void MarkingState::createException(){
    
}

void MarkingState::validate(){
    
}

void MarkingState::fail(){
    
}

//----------- ExceptionState -------------------------------------

void ExceptionState::pause(){
    
}

//----------- PausedState ----------------------------------------

void PausedState::resumeMarking(){
    
}

//----------- ValidatedState -------------------------------------

void ValidatedState::marked(){
    
}

//----------- MarkedState ----------------------------------------

void MarkedState::captureMarks(){
    
}

//----------- CapturedState --------------------------------------

void CapturedState::archive(){
    
}

//----------- FailedState ----------------------------------------

void FailedState::pause(){
    
}

//----------- end. -----------------------------------------------
