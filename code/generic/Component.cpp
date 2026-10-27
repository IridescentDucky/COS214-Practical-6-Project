#include "Component.h"

#include <iostream>

void Component::add(Component*) {
    std::cout << "(component) Could not add" << std::endl;
}

void Component::remove(Component*) {
    std::cout << "(component) Could not remove" << std::endl;
}

Component* Component::getChild(int n) {
    std::cout << "(component) Could not get" << std::endl;
    
    return nullptr;
}

Component::~Component(){
    
}