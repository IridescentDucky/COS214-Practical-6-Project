#include "Composite.h"

using namespace std;

template <typename T>
void Composite<T>::display(int indent = 0) {
    for (int i = 0; i < indent; i++)
    {
        cout << "  ";
    }       

    cout << this->name << endl;

    for (auto child : children) {
        child->display(++indent);
    }
}

template <typename T>
void Composite<T>::add(Component<T>* c) {
    children.push_back(c);
}

template <typename T>
void Composite<T>::remove(Component<T>* c) {
    children.remove(c);
}

template <typename T>
Component<T>* Composite<T>::getChild(int n) {
    if (n < 0 || n >= (int) children.size()) {
        cout << "(Composite) out of bounds" << endl;

        return nullptr;
    }

    list<Component*>::iterator it = next(children.begin(), n);
    return *it; 
}

template <typename T>
Composite<T>::~Composite() {
    for (list<Component*>::iterator it = children.begin(); it != children.end(); ++it) {
        delete *it;
    }
};	