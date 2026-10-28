#include "Creator.h"

Creator::~Creator(){

    //im not delting AbstractWorkItem here, its def causing mem leaks, might default it
}

AbstractWorkItem* Creator::createWorkItem(){

    return factoryMethod(); //followed Chocolate example in lecture slides
}