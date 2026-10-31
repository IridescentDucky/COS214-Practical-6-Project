#include "WorkflowMediator.h"
#include "WorkItem.h"
#include "WorkItemIterator.h"
#include "ConcreteHandlerA.h"
#include "ConcreteHandlerB.h"
#include "ConcreteHandlerC.h"
#include "ConcreteHandlerD.h"
#include "ConcreteHandlerE.h"
#include "ConcreteStrategyA.h"
#include "Adapter.h"

#include <iostream>

template <typename T>
WorkflowMediator<T>::WorkflowMediator()
    : strategy(new ConcreteStrategyA<T>()), externalSystem(new Adaptee()), external(new Adapter(externalSystem))
{
}

template <typename T>
WorkflowMediator<T>::~WorkflowMediator()
{
    for (TaskEscalationManager<T>* escalation : escalations)
    {
        delete escalation;
    }
    for (AbstractWorkItem<T>* item : workItems)
    {
        delete item;
    }
    delete strategy;
    delete external;
    delete externalSystem;
}

template <typename T>
void WorkflowMediator<T>::addWorkItem(AbstractWorkItem<T>* item)
{
    if (item != nullptr && getWorkItem(item->getId()) == nullptr)
    {
        workItems.push_back(item);

        TaskEscalationManager<T>* teamLead = new ConcreteHandlerA<T>("Team lead", 3);
        TaskEscalationManager<T>* manager = new ConcreteHandlerB<T>("Manager", 7);
        TaskEscalationManager<T>* departmentHead = new ConcreteHandlerC<T>("Department head", 12);
        TaskEscalationManager<T>* director = new ConcreteHandlerD<T>("Director", 18);
        teamLead->setSuccessor(manager);
        manager->setSuccessor(departmentHead);
        departmentHead->setSuccessor(director);
        director->setSuccessor(new ConcreteHandlerE<T>("Executive", 25));
        item->attach(teamLead);
        escalations.push_back(teamLead);
    }
}

template <typename T>
AbstractWorkItem<T>* WorkflowMediator<T>::getWorkItem(int id) const
{
    for (AbstractWorkItem<T>* item : workItems)
    {
        if (item->getId() == id)
        {
            return item;
        }
    }
    return nullptr;
}

template <typename T>
const std::vector<AbstractWorkItem<T>*>& WorkflowMediator<T>::getWorkItems() const
{
    return workItems;
}

template <typename T>
Iterator<T>* WorkflowMediator<T>::createIterator() const
{
    return new WorkItemIterator<T>(this);
}

template <typename T>
bool WorkflowMediator<T>::addDependency(int predecessorId, int successorId)
{
    if (predecessorId == successorId || getWorkItem(predecessorId) == nullptr ||
        getWorkItem(successorId) == nullptr)
    {
        return false;
    }

    std::vector<int>& successors = dependencies[predecessorId];
    for (std::vector<int>::const_iterator it = successors.begin(); it != successors.end(); ++it)
    {
        if (*it == successorId)
        {
            return false;
        }
    }

    successors.push_back(successorId);
    return true;
}

template <typename T>
void WorkflowMediator<T>::notify(AbstractWorkItem<T>* colleague)
{
    if (colleague == nullptr || colleague->getStateName() != "Completed")
    {
        return;
    }

    strategy->algorithm(colleague);
    std::cout << "  [Mediator] Telling the external system that " << colleague->getName() << " is complete" << std::endl;
    external->request();

    std::map<int, std::vector<int> >::const_iterator dependency = dependencies.find(colleague->getId());
    if (dependency == dependencies.end())
    {
        return;
    }

    for (std::vector<int>::const_iterator it = dependency->second.begin(); it != dependency->second.end(); ++it)
    {
        AbstractWorkItem<T>* successor = getWorkItem(*it);
        if (successor != nullptr && successor->getStateName() == "Created")
        {
            successor->handleState();
        }
    }
}

template <typename T>
void WorkflowMediator<T>::setStrategy(Strategy<T>* strategy)
{
    if (strategy == nullptr || strategy == this->strategy)
    {
        return;
    }
    delete this->strategy;
    this->strategy = strategy;
}

template <typename T>
int WorkflowMediator<T>::savePrototype(AbstractWorkItem<T>* item)
{
    if (item == nullptr)
    {
        return -1;
    }
    prototypes.addPrototype(item->clone(0, nullptr));
    return prototypes.getPrototypeCount() - 1;
}

template <typename T>
AbstractWorkItem<T>* WorkflowMediator<T>::createFromPrototype(int index, int id)
{
    AbstractWorkItem<T>* prototype = prototypes.getPrototype(index);
    if (prototype == nullptr || getWorkItem(id) != nullptr)
    {
        return nullptr;
    }
    AbstractWorkItem<T>* item = prototype->clone(id, this);
    addWorkItem(item);
    return item;
}

template class WorkflowMediator<int>;
