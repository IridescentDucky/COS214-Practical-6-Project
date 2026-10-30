#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

#include "AbstractGame.h"

#include <string>

class GameFactory{
public:
    virtual ~GameFactory();
    AbstractGame* createGame(std::string name,std::string description,std::string ageRating);

protected:
    virtual AbstractGame* factoryMethod(std::string name, std::string description, std::string ageRating) = 0;        
};    

#endif