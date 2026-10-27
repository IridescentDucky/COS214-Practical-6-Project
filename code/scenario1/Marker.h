#ifndef MARKER_h
#define MARKER_h

#include <string>

class AbstractExamPaper;

class Marker{
    
protected:
    Marker* next;
    std::string tutorId;
    std::string name;
    
public:
    Marker(std::string id, std::string markerName): next(nullptr), tutorId(id), name(markerName) {}
    virtual ~Marker() = default;
    
    bool canHandle(AbstractExamPaper* paper){
        // Not sure how we want this to work just yet
        
        return true;
    };
    
    void setNext(Marker* marker){
        this->next = marker;
    };
    
    virtual void handle(AbstractExamPaper* paper) = 0;
    virtual void update() = 0;
};

#endif
