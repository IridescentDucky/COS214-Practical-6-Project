#ifndef COMPONENT_H
#define COMPONENT_H

/** @brief Common interface for individual and composite workflow components. */
template <typename T>
class Component {
private:
    T info;
public:
    /** @brief Displays this component.
     *  @param indent Indentation level used for hierarchical output.
     */
    virtual void display(int indent = 0) = 0;

    /** @brief Adds a child component when supported. */
    virtual void add(Component<T>*);
    /** @brief Removes a child component when supported. */
    virtual void remove(Component<T>*);
    /** @brief Gets a child component by index when supported.
     *  @param n Zero-based child index.
     *  @return The requested child, or null when unavailable.
     */
    virtual Component<T>* getChild(int n);

    /** @brief Destroys the component through its base interface. */
    virtual ~Component();

    /** @brief Gets the component's score. */
    virtual int getScore() = 0;
    /** @brief Gets the component's time allowance. */
    virtual int getTime() = 0;
};


#endif
