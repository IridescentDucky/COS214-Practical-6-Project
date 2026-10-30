#ifndef CONCRETEGAMEFACTORY_H
#define CONCRETEGAMEFACTORY_H

#include "GameFactory.h"

class ConcreteGameFactory : public GameFactory {

protected:
    AbstractGame* factoryMethod(std::string name, std::string description, std::string ageRating);
};


#endif
