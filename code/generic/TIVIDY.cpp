#include "TIVIDY.h"
#include "WorkItem.h"
#include "WorkflowMediator.h"

#include <iostream>

template <typename T>
TIVIDY<T>::TIVIDY() : mediator(new WorkflowMediator<T>()), nextId(1)
{
}

template <typename T>
TIVIDY<T>::~TIVIDY()
{
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
    AbstractWorkItem<T>* item = new WorkItem(nextId++, name, deadline, mediator);
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
void TIVIDY<T>::printStatus() const
{
    std::cout << "  [TIVIDY] Work items:" << std::endl;
    for (AbstractWorkItem<T>* item : mediator->getWorkItems())
    {
        std::cout << "    " << item->getId() << " " << item->getName() << ": " << item->getStateName() << std::endl;
    }
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
