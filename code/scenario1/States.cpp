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
    completeMarking();
}

void MarkingState::createException() {
    if (paper != nullptr) {
        paper->setState(new ExceptionState(paper));
    }
}

void MarkingState::validate() {
    if (paper != nullptr) {
        paper->setState(new ValidatedState(paper));
    }
}

void MarkingState::fail() {
    if (paper != nullptr) {
        paper->setState(new FailedState(paper));
    }
}

void ExceptionState::pause() {
    if (paper != nullptr) {
        paper->setState(new PausedState(paper));
    }
}

void PausedState::resumeMarking() {
    if (paper != nullptr) {
        paper->setState(new MarkingState(paper));
    }
}

void ValidatedState::nextState() {
    if (paper != nullptr) {
        paper->setState(new MarkedState(paper));
    }
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
