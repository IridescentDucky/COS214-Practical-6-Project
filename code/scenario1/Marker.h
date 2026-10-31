#ifndef MARKER_h
#define MARKER_h

#include <string>

class AbstractExamPaper;

class Marker {
protected:
    Marker* next;
    std::string tutorId;
    std::string name;
    AbstractExamPaper* paper;

public:
    Marker(std::string id, std::string markerName)
        : next(nullptr), tutorId(id), name(markerName), paper(nullptr) {}
    virtual ~Marker();

    void setNext(Marker* marker) {
        next = marker;
    }

    bool forwardToNext(AbstractExamPaper* paper) const {
        if (next == nullptr) {
            return false;
        }
        next->handle(paper);
        return true;
    }

    virtual void handle(AbstractExamPaper* paper) = 0;
    virtual void update() = 0;

    void setExamPaper(AbstractExamPaper* paper) { this->paper = paper;}
};

#endif
