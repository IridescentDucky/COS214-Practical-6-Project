#include "Markers.h"
#include "AbstractExamPaper.h"
#include <iostream>


//----------- Tutor ----------------------------------------------

Tutor::Tutor(std::string id, std::string name) : Marker(id, name) {}

void Tutor::handle(AbstractExamPaper* paper) {

    if (this->canHandle(paper) == false){
        std::cout << "[Tutor] unable to handle examp paper: " << paper << " will pass to next handler." << std::endl;
        this->next->handle(paper);
    }
    
    paper->mark();
}

void Tutor::update() {
    
    // needs implementation
}


//----------- AssistantLecturer ----------------------------------

AssistantLecturer::AssistantLecturer(std::string id, std::string name) : Marker(id, name) {}

void AssistantLecturer::handle(AbstractExamPaper* paper) {
    
    if (this->canHandle(paper) == false){
        std::cout << "[AssistantLecturer] unable to handle examp paper: " << paper << " will pass to next handler." << std::endl;
        this->next->handle(paper);
    }
    
    paper->mark();
}

void AssistantLecturer::update() {
    
    // needs implementation
}

//----------- Lecturer -------------------------------------------

Lecturer::Lecturer(std::string id, std::string name) : Marker(id, name) {}

void Lecturer::handle(AbstractExamPaper* paper) {
    
    if (this->canHandle(paper) == false){
        std::cout << "[Lecturer] unable to handle examp paper: " << paper << " will pass to next handler." << std::endl;
        this->next->handle(paper);
    }
    
    paper->mark();
}

void Lecturer::update() {
    
    // needs implementation
}

//----------- ModuleCoordinator ----------------------------------

ModuleCoordinator::ModuleCoordinator(std::string id, std::string name) : Marker(id, name) {}

void ModuleCoordinator::handle(AbstractExamPaper* paper) {
    
    if (this->canHandle(paper) == false){
        std::cout << "[ModuleCoordinator] unable to handle examp paper: " << paper << " will pass to next handler." << std::endl;
        this->next->handle(paper);
    }
    
    paper->mark();
}

void ModuleCoordinator::update() {
    
    // needs implementation
}

//----------- end. -----------------------------------------------
