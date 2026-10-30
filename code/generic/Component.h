#ifndef COMPONENT_H
#define COMPONENT_H

template <typename T>
class Component {
private:
    T info;
public:
    virtual void display(int indent = 0) = 0;

    virtual void add(Component<T>*);
    virtual void remove(Component<T>*);
    virtual Component<T>* getChild(int n);

    virtual ~Component();

    virtual int getScore() = 0;
    virtual int getTime() = 0;
};


#endif
