#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "Component.h"

#include <iostream>
#include <list>

using namespace std;

class Composite: public Component {
public:	
	void operation();
	void add(Component*);
    void remove(Component*);
    Component* getChild(int n);

    ~Composite();
private:
	list<Component*> children;
};

#endif