#include "ConcreteGameFactory.h"

#include "Game.h"

AbstractGame* ConcreteGameFactory::factoryMethod(std::string name, std::string description, std::string ageRating) {
    
    return new Game(name, description, ageRating);
}