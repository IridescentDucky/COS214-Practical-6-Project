#include "Creator.h"

template <typename T>
Creator<T>::~Creator(){

    //im not delting AbstractWorkItem here, its def causing mem leaks, might default it
}

template <typename T>
AbstractWorkItem<T>* Creator<T>::createWorkItem(){

    return factoryMethod(); //followed Chocolate example in lecture slides
}