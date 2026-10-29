#ifndef CREATOR_H
#define CREATOR_H

#include "AbstractWorkItem.h"

template <typename T>
class Creator {
public:
    virtual ~Creator();
    AbstractWorkItem<T>* createWorkItem(); //followed Chocolate example in lecture slides

protected:
    virtual AbstractWorkItem<T>* factoryMethod() = 0;

// private:
//     AbstractWorkItem* item; //note we dont really need this, we arent using it anywhere

};

#endif