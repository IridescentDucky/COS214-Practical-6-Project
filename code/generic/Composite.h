#ifndef COMPOSITE_H
#define COMPOSITE_H

#include "Component.h"

#include <iostream>
#include <list>

using namespace std;

/** @brief Composite component that groups child components. */
template <typename T>
class Composite: public Component<T> {
public:	
    /** @brief Creates a composite with the given name.
     *  @param name Display name for the group.
     */
    Composite(const string& name);
    /** @brief Displays this composite and its children.
     *  @param indent Indentation level used for hierarchical output.
     */
	void display(int indent = 0);
    /** @brief Adds a child component to the group. */
	void add(Component<T>*);
    /** @brief Removes a child component from the group. */
    void remove(Component<T>*);
    /** @brief Gets a child component by index.
     *  @param n Zero-based child index.
     *  @return The child at that index, or null when out of range.
     */
    Component<T>* getChild(int n);

    /** @brief Calculates the combined score of the children. */
    int getScore();
    /** @brief Calculates the combined time allowance of the children. */
    int getTime();

    /** @brief Releases the composite's child collection. */
    ~Composite();
private:
    string name;
	list<Component<T>*> children;
};

#endif