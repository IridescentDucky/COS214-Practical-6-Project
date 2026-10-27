#include "Composite.h"

using namespace std;

void Composite::operation() {
    cout << "(Composite) Did something" << endl;
}

void Composite::add(Component* c) {
    children.push_back(c);
}

void Composite::remove(Component* c) {
    children.remove(c);
}

Component* Composite::getChild(int n) {
    if (n < 0 || n > (int) children.size()) {
        cout << "(Composite) out of bounds" << endl;

        return nullptr;
    }

    list<Component*>::iterator it = next(children.begin(), n);
    return *it; 
}

Composite::~Composite() {
    for (list<Component*>::iterator it = children.begin(); it != children.end(); ++it) {
        delete *it;
    }
};	