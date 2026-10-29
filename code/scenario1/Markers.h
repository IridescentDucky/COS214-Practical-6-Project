#ifndef Markers_h
#define Markers_h

#include "Marker.h"
#include <string>
class AbstractExamPaper;

//----------- Tutor ----------------------------------------------

class Tutor :public Marker{
    
public:
    Tutor(std::string id, std::string name);
    
    void handle(AbstractExamPaper* paper) override;
    void update() override;
};

//----------- AssistantLecturer ----------------------------------

class AssistantLecturer :public Marker{
    
public:
    AssistantLecturer(std::string id, std::string name);
    
    void handle(AbstractExamPaper* paper) override;
    void update() override;
};

//----------- Lecturer -------------------------------------------

class Lecturer :public Marker{
    
public:
    Lecturer(std::string id, std::string name);
    
    void handle(AbstractExamPaper* paper) override;
    void update() override;
};

//----------- ModuleCoordinator ----------------------------------

class ModuleCoordinator :public Marker{
    
public:
    ModuleCoordinator(std::string id, std::string name);
    
    void handle(AbstractExamPaper* paper) override;
    void update() override;
};

//----------- end. -----------------------------------------------

#endif
