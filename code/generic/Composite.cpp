#include "Composite.h"

using namespace std;

template <typename T>
void Composite<T>::display(int indent) {
    for (int i = 0; i < indent; i++)
    {
        cout << "  ";
    }       

    // if we need better terminal output
    // └
    // ├
    // ─
    // │

    cout << this->name << endl;

    for (auto child : this->children) {
        child->display(indent + 1);
    }
}

template <typename T>
void Composite<T>::add(Component<T>* c) {
    this->children.push_back(c);
}

template <typename T>
void Composite<T>::remove(Component<T>* c) {
    this->children.remove(c);
}

template <typename T>
Component<T>* Composite<T>::getChild(int n) {
    if (n < 0 || n >= (int) children.size()) {
        cout << "(Composite) out of bounds" << endl;

        return nullptr;
    }

    typename list<Component<T>*>::iterator it = next(this->children.begin(), n);
    return *it; 
}

template <typename T>
Composite<T>::~Composite() {
    for (typename list<Component<T>*>::iterator it = this->children.begin(); it != this->children.end(); ++it) {
        delete *it;
    }
};	