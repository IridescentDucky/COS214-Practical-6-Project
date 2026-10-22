#include "ConcreteHandler1.h"
#include <iostream>

void ConcreteHandler1::handleRequest(){
    
    bool canHandle = false;
    
    // Placeholder demo handler: it deliberately passes the request onward.
    
    if(canHandle){
        std::cout << "[ConcreteHandler1] Can handle." << std::endl;
    }
    else if( this->successor != nullptr){
        std::cout << "[ConcreteHandler1] Cannot handle, passing on to successor..." << std::endl;
        this->successor->handleRequest();
    }
    else{
        std::cout << "[ConcreteHandler1] End of chain reached. Request could not be handled." << std::endl;
    }
        
    return;
}
