#include "PrototypeManager.h"
#include <iostream>


template <typename T>
void PrototypeManager<T>::resize(int cap) {
    AbstractWorkItem<T>** temp = new AbstractWorkItem<T>*[cap];

    for (int i = 0; i < size; ++i) {
        temp[i] = workitems[i];
    }
    
    delete[] this->workitems;
    
    this->workitems = temp;
    this->capacity = cap;
}

template <typename T>
PrototypeManager<T>::PrototypeManager(int cap) : size(0), capacity(cap) {
    this->workitems = new AbstractWorkItem<T>*[capacity];

    for (int i = 0; i < capacity; ++i) {
        this->workitems[i] = nullptr;
    }
}

template <typename T>
PrototypeManager<T>::~PrototypeManager() {
    for (int i = 0; i < size; ++i) {
        delete this->workitems[i];
    }

    delete[] this->workitems;
}

template <typename T>
void PrototypeManager<T>::addPrototype(AbstractWorkItem<T>* item) {
    if (item == nullptr) {
        return;
    }
    
    if (this->size >= this->capacity) {
        resize(this->capacity * 2);
    }

    this->workitems[size++] = item;
}

template <typename T>
void PrototypeManager<T>::removePrototype(AbstractWorkItem<T>* item) {
    int index = -1;
    for (int i = 0; i < size; ++i) {
        if (workitems[i] == item) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        delete this->workitems[index];
        
        for (int i = index; i < size - 1; ++i) {
            this->workitems[i] = this->workitems[i + 1];
        }

        size--;
        this->workitems[size] = nullptr;
    }
}

template <typename T>
AbstractWorkItem<T>* PrototypeManager<T>::getPrototype(int index) {
    if (index < 0 || index >= size) {
        std::cout << "index out of bounds" << std::endl;

        return nullptr;
    }

    return this->workitems[index];
}