#ifndef PROTOTYPEMANAGER_H
#define PROTOTYPEMANAGER_H

#include <vector>

template <typename T>
class AbstractWorkItem;

/** @brief Owns and indexes work-item prototypes for later cloning. */
template <typename T>
class PrototypeManager
{
public:
    /** @brief Creates an empty prototype registry. */
    PrototypeManager();
    /** @brief Releases the prototypes held by this registry. */
    ~PrototypeManager();
    PrototypeManager(const PrototypeManager&) = delete;
    PrototypeManager& operator=(const PrototypeManager&) = delete;

    /** @brief Adds a prototype to the registry.
     *  @param prototype Prototype to store.
     */
    void addPrototype(AbstractWorkItem<T>* prototype);
    /** @brief Removes a prototype from the registry.
     *  @param prototype Prototype to remove.
     */
    void removePrototype(AbstractWorkItem<T>* prototype);
    /** @brief Gets a prototype by index.
     *  @param n Zero-based prototype index.
     *  @return The prototype, or null if the index is invalid.
     */
    AbstractWorkItem<T>* getPrototype(int n) const;
    /** @brief Gets the number of registered prototypes.
     *  @return Prototype count.
     */
    int getPrototypeCount() const;

private:
    std::vector<AbstractWorkItem<T>*> workItems;
};

#endif
