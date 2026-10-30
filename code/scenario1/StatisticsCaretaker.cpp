#include "StatisticsCaretaker.h"
#include "StatisticsMemento.h"
#include <iostream>

StatisticsCaretaker::StatisticsCaretaker() : memento(nullptr) {}

StatisticsCaretaker::~StatisticsCaretaker() {
    
    if (memento != nullptr) {
        delete memento;
        memento = nullptr;
    }
}

StatisticsMemento* StatisticsCaretaker::getMemento() const {
    
    std::cout << "[StatisticsCaretaker] Retrieved memento." << std::endl;
    return memento;
}

void StatisticsCaretaker::saveMemento(StatisticsMemento* m) {
    
    if (memento != nullptr) {
        
        delete memento;
    }
    
    memento = m;
    std::cout << "[StatisticsCaretaker] Saved new memento snapshot." << std::endl;
}
