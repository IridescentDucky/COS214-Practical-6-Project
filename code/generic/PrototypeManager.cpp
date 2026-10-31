#include "PrototypeManager.h"
#include "AbstractWorkItem.h"

#include <algorithm>

template <typename T>
PrototypeManager<T>::PrototypeManager()
{
}

template <typename T>
PrototypeManager<T>::~PrototypeManager()
{
    for (AbstractWorkItem<T>* prototype : workItems)
    {
        delete prototype;
    }
}

template <typename T>
void PrototypeManager<T>::addPrototype(AbstractWorkItem<T>* prototype)
{
    if (prototype != nullptr && std::find(workItems.begin(), workItems.end(), prototype) == workItems.end())
    {
        workItems.push_back(prototype);
    }
}

template <typename T>
void PrototypeManager<T>::removePrototype(AbstractWorkItem<T>* prototype)
{
    typename std::vector<AbstractWorkItem<T>*>::iterator it = std::find(workItems.begin(), workItems.end(), prototype);
    if (it != workItems.end())
    {
        delete *it;
        workItems.erase(it);
    }
}

template <typename T>
AbstractWorkItem<T>* PrototypeManager<T>::getPrototype(int n) const
{
    if (n < 0 || n >= static_cast<int>(workItems.size()))
    {
        return nullptr;
    }
    return workItems[n];
}

template <typename T>
int PrototypeManager<T>::getPrototypeCount() const
{
    return static_cast<int>(workItems.size());
}

template class PrototypeManager<int>;
