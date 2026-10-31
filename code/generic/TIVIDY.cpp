#include "TIVIDY.h"
#include "WorkItem.h"
#include "WorkflowMediator.h"
#include "ConcreteCreator.h"

#include <iostream>

template <typename T>
TIVIDY<T>::TIVIDY() : mediator(new WorkflowMediator<T>()), creator(new ConcreteCreator<T>()), nextId(1)
{
}

template <typename T>
TIVIDY<T>::~TIVIDY()
{
    delete creator;
    delete mediator;
}

template <typename T>
AbstractWorkItem<T>* TIVIDY<T>::find(int id) const
{
    AbstractWorkItem<T>* item = mediator->getWorkItem(id);
    if (item == nullptr)
    {
        std::cout << "  [TIVIDY] No work item with id " << id << std::endl;
    }
    return item;
}

template <typename T>
int TIVIDY<T>::createWorkItem(const std::string& name, int deadline)
{
    AbstractWorkItem<T>* item = creator->createWorkItem(nextId++, name, deadline, mediator);
    mediator->addWorkItem(item);
    std::cout << "  [TIVIDY] Created '" << name << "' (id " << item->getId() << ")" << std::endl;
    return item->getId();
}

template <typename T>
void TIVIDY<T>::advanceWork(int id)
{
    AbstractWorkItem<T>* item = find(id);
    if (item != nullptr)
    {
        item->handleState();
    }
}

template <typename T>
void TIVIDY<T>::submitWork(int id, const std::string& data)
{
    AbstractWorkItem<T>* item = find(id);
    if (item != nullptr)
    {
        item->set(data);
        item->handleState();
    }
}

template <typename T>
void TIVIDY<T>::pauseWork(int id)
{
    AbstractWorkItem<T>* item = find(id);
    if (item != nullptr)
    {
        item->paused();
    }
}

template <typename T>
void TIVIDY<T>::resumeWork(int id)
{
    AbstractWorkItem<T>* item = find(id);
    if (item != nullptr)
    {
        item->resume();
    }
}

template <typename T>
void TIVIDY<T>::logTime(int id, int units)
{
    if (units <= 0)
    {
        std::cout << "  [TIVIDY] Time logged must be positive" << std::endl;
        return;
    }
    AbstractWorkItem<T>* item = find(id);
    if (item != nullptr)
    {
        item->addTimeSpent(units);
    }
}

template <typename T>
void TIVIDY<T>::addTask(int id, const std::string& name, int score, int maxScore)
{
    if (score < 0 || maxScore <= 0 || score > maxScore)
    {
        std::cout << "  [TIVIDY] Task score must be between 0 and a positive maximum" << std::endl;
        return;
    }
    AbstractWorkItem<T>* item = find(id);
    if (item != nullptr)
    {
        item->addTask(name, score, maxScore);
    }
}

template <typename T>
void TIVIDY<T>::setStrategy(Strategy<T>* strategy)
{
    mediator->setStrategy(strategy);
}

template <typename T>
int TIVIDY<T>::saveAsTemplate(int id)
{
    AbstractWorkItem<T>* item = find(id);
    if (item == nullptr)
    {
        return -1;
    }
    int index = mediator->savePrototype(item);
    std::cout << "  [TIVIDY] Saved '" << item->getName() << "' as template " << index << std::endl;
    return index;
}

template <typename T>
int TIVIDY<T>::createFromTemplate(int templateIndex)
{
    AbstractWorkItem<T>* item = mediator->createFromPrototype(templateIndex, nextId);
    if (item == nullptr)
    {
        std::cout << "  [TIVIDY] No template " << templateIndex << std::endl;
        return -1;
    }
    nextId++;
    std::cout << "  [TIVIDY] Created '" << item->getName() << "' (id " << item->getId() << ") from template " << templateIndex << std::endl;
    return item->getId();
}

template <typename T>
bool TIVIDY<T>::addDependency(int predecessorId, int successorId)
{
    return mediator->addDependency(predecessorId, successorId);
}

template <typename T>
std::string TIVIDY<T>::getWorkItemState(int id) const
{
    AbstractWorkItem<T>* item = find(id);
    return item != nullptr ? item->getStateName() : "";
}

template <typename T>
Iterator<T>* TIVIDY<T>::createIterator() const
{
    return mediator->createIterator();
}

template <typename T>
void TIVIDY<T>::printStatus() const
{
    std::cout << "  [TIVIDY] Work items:" << std::endl;
    Iterator<T>* it = mediator->createIterator();
    while (it->hasNext())
    {
        AbstractWorkItem<T>* item = it->next();
        std::cout << "    " << item->getId() << " " << item->getName() << ": " << item->getStateName() << std::endl;
    }
    delete it;
}

// AbstractWorkflowFactory was removed

// template <typename T>
// void TIVIDY<T>::runWorkflow(AbstractWorkflowFactory<T>* factory){
//     if (factory == nullptr)
//     {
//         std::cout << "  [TIVIDY] Cannot run a null workflow factory." << std::endl;
//         return;
//     }

//     //basically using same factory create products A and B...

//     AbstractWorkflowInstanceA* instanceA = factory->createWorkflowInstanceA();

//     AbstractWorkflowInstanceB* instanceB = factory->createWorkflowInstanceB();

//     instanceA->create();
//     instanceB->create();

//     delete instanceA;
//     delete instanceB;
// }

template class TIVIDY<int>;
