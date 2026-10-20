#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
public:
	virtual void operation() = 0;
	virtual void add(Component*) = 0;
    virtual void remove(Component*) = 0;
    virtual Component* getChild(int n) = 0;

    virtual ~Component() {};
};

#endif