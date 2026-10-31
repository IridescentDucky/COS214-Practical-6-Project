#ifndef PROTOTYPEMANAGER_H
#define PROTOTYPEMANAGER_H

#include <vector>

template <typename T>
class AbstractWorkItem;

template <typename T>
class PrototypeManager
{
public:
    PrototypeManager();
    ~PrototypeManager();
    PrototypeManager(const PrototypeManager&) = delete;
    PrototypeManager& operator=(const PrototypeManager&) = delete;

    void addPrototype(AbstractWorkItem<T>* prototype);
    void removePrototype(AbstractWorkItem<T>* prototype);
    AbstractWorkItem<T>* getPrototype(int n) const;
    int getPrototypeCount() const;

private:
    std::vector<AbstractWorkItem<T>*> workItems;
};

#endif
