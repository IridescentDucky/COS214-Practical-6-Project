#ifndef CONCRETECREATOR_H
#define CONCRETECREATOR_H

#include "Creator.h"


class ConcreteCreator : public Creator{

protected:
    AbstractWorkItem* factoryMethod();

};



#endif