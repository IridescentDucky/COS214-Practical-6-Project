#include "Composite.h"

using namespace std;

void operation() {
    cout << "(Composite) Did something"
}

void add(Component* c) {
    children.push_back(c);
}

void remove(Component*) {
    l.remove(g);
}

void getChild(int n) {
    if (n < 0 || n > children.size()) {
        cout << "(Composite) out of bounds" << endl;

        return;
        //return null; // if we want to return a *
    }

    list<Graphic*>::iterator it = next(children.begin(), index);
    
    cout << "(Composite) Child: " << it->operation() << endl;    
    // return *it; 
}

~Component() {
    for (list<Graphic*>::iterator it = children.begin(); it != children.end(); ++it) {
        delete *it;
    }
};	