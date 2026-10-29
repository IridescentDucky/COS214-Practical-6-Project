#include "Markers.h"

Tutor::Tutor(std::string id, std::string name) : Marker(id, name) {}

void Tutor::handle(AbstractExamPaper*) {
    // TODO: implement marking and escalation behavior.
}

void Tutor::update() {
    // TODO: respond to delivery notifications.
}

AssistantLecturer::AssistantLecturer(std::string id, std::string name) : Marker(id, name) {}

void AssistantLecturer::handle(AbstractExamPaper*) {
    // TODO: implement marking and escalation behavior.
}

void AssistantLecturer::update() {
    // TODO: respond to delivery notifications.
}

Lecturer::Lecturer(std::string id, std::string name) : Marker(id, name) {}

void Lecturer::handle(AbstractExamPaper*) {
    // TODO: implement marking and escalation behavior.
}

void Lecturer::update() {
    // TODO: respond to delivery notifications.
}

ModuleCoordinator::ModuleCoordinator(std::string id, std::string name) : Marker(id, name) {}

void ModuleCoordinator::handle(AbstractExamPaper*) {
    // TODO: implement marking and escalation behavior.
}

void ModuleCoordinator::update() {
    // TODO: respond to delivery notifications.
}
