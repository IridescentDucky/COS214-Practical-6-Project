#include "Composite.h"

using namespace std;

template <typename T>
Composite<T>::Composite(const string& name) : name(name) {
}

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
int Composite<T>::getScore() {
    int total = 0;
    for (auto child : this->children) {
        total += child->getScore();
    }
    return total;
}

template <typename T>
int Composite<T>::getTime() {
    int total = 0;
    for (auto child : this->children) {
        total += child->getTime();
    }
    return total;
}

template <typename T>
Composite<T>::~Composite() {
}	

template class Composite<int>;
