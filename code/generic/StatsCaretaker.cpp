#include "StatsCaretaker.h"
#include "StatsMemento.h"
#include <iostream>


StatsCaretaker::StatsCaretaker() : memento(nullptr) {}

StatsCaretaker::~StatsCaretaker() {
    
    if (memento != nullptr) {
        delete memento;
        memento = nullptr;
    }
}

StatsMemento* StatsCaretaker::getMemento() const {
    
    std::cout << "[StatsCaretaker] Retrieved memento." << std::endl;
    return memento;
}

void StatsCaretaker::saveMemento(StatsMemento* m) {
    
    if (memento != nullptr) {
        
        delete memento;
    }
    
    memento = m;
    std::cout << "[StatsCaretaker] Saved new memento snapshot." << std::endl;
}
