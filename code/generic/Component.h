#ifndef COMPONENT_H
#define COMPONENT_H

class Component{

public:
    virtual void operation() = 0;

    virtual void add(Component*);
    virtual void remove(Component*);
    virtual Component* getChild(int n);

    virtual ~Component();

    virtual int getScore() = 0;
    virtual int getTime() = 0;
};


#endif
