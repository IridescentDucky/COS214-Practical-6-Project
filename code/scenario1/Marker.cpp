#include "Marker.h"

#include "AbstractExamPaper.h"

Marker::~Marker() {
    if (paper != nullptr) {
        AbstractExamPaper* attachedPaper = paper;
        paper = nullptr;
        attachedPaper->detach(this);
    }
}
