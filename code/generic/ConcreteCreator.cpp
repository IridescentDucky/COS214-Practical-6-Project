#include "ConcreteCreator.h"
#include "WorkItem.h"

#include <iostream>

AbstractWorkItem* ConcreteCreator::factoryMethod(){

    std::cout << "Creating a WorkItem" << std::endl;
    return new WorkItem();
}