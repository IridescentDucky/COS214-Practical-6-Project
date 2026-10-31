#include "AbstractExamPaper.h"
#include "States.h"

#include <iostream>

PaperState::~PaperState() = default;

void WrittenState::nextState() {
    if (paper != nullptr) {
        paper->setState(new DeliveredState(paper));
    }
}

void DeliveredState::nextState() {
    if (paper != nullptr) {
        paper->setState(new MarkingState(paper));
    }
}

void MarkingState::pause() {
    if (paper != nullptr) {
        paper->setState(new PausedState(paper));
    }
}

void MarkingState::completeMarking() {
    if (paper != nullptr) {
        paper->setState(new MarkedState(paper));
    }
}

void MarkingState::nextState() {
}

void MarkingState::createException() {
}

void MarkingState::validate() {
}

void MarkingState::fail() {
}

void ExceptionState::pause() {
}

void PausedState::resumeMarking() {
    if (paper != nullptr) {
        paper->setState(new MarkingState(paper));
    }
}

void ValidatedState::nextState() {
}

void MarkedState::nextState() {
    if (paper != nullptr) {
        paper->setState(new CapturedState(paper));
    }
}

void CapturedState::nextState() {
    if (paper != nullptr) {
        paper->setState(nullptr);
    }
}

void FailedState::pause() {
}
