#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "Component.h"

#include <iostream>
#include <list>

using namespace std;

template <typename T>
class Composite: public Component<T> {
public:	
    Composite(const string& name);
	void display(int indent = 0);
	void add(Component<T>*);
    void remove(Component<T>*);
    Component<T>* getChild(int n);

    int getScore();
    int getTime();

    ~Composite();
private:
    string name;
	list<Component<T>*> children;
};

#endif