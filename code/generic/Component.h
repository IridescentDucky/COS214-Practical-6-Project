#ifndef COMPONENT_H
#define COMPONENT_H

template <typename T>
class Component {
private:
    T info;
public:
    virtual void display(int indent = 0) = 0;

    virtual void add(Component*);
    virtual void remove(Component*);
    virtual Component* getChild(int n);

    virtual ~Component();
};


#endif