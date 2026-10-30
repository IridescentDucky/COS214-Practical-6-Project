#include "ConcreteCreator.h"
#include "WorkItem.h"

#include <iostream>


template <typename T>
AbstractWorkItem<T>* ConcreteCreator<T>::factoryMethod(){
    std::cout << "Creating a WorkItem" << std::endl;

    return new WorkItem<T>(0, "WorkItem", 0, nullptr);
}

template class ConcreteCreator<int>;
