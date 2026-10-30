#include "GameFactory.h"

GameFactory::~GameFactory() {

}

AbstractGame* GameFactory::createGame(std::string name, std::string description, std::string ageRating) {
    
    return factoryMethod(name, description, ageRating);
}