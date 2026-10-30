#include "Decorator.h"

template <typename T>
Decorator<T>::Decorator(Component<T>* component){
    
    this->component = component;
}

template <typename T>
Decorator<T>::~Decorator(){

}

template <typename T>
void Decorator<T>::display(int indent){
    
    this->component->display(indent);
}

template <typename T>
int Decorator<T>::getScore() {
    return component->getScore();
}

template <typename T>
int Decorator<T>::getTime() {
    return component->getTime();
}

template class Decorator<int>;
