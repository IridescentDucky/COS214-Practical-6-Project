#include "Component.h"

#include <iostream>

template <typename T>
void Component<T>::add(Component<T>*) {
    std::cout << "(component) Could not add" << std::endl;
}

template <typename T>
void Component<T>::remove(Component<T>*) {
    std::cout << "(component) Could not remove" << std::endl;
}

template <typename T>
Component<T>* Component<T>::getChild(int n) {
    std::cout << "(component) Could not get" << std::endl;
    
    return nullptr;
}

template <typename T>
Component<T>::~Component(){
    
}