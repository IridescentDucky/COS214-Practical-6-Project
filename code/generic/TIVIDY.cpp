#include "TIVIDY.h"
#include "WorkItem.h"
#include "WorkflowMediator.h"

#include <iostream>

TIVIDY::TIVIDY() : mediator(new WorkflowMediator()), nextId(1)
{
}

TIVIDY::~TIVIDY()
{
    delete mediator;
}

AbstractWorkItem* TIVIDY::find(int id) const
{
    AbstractWorkItem* item = mediator->getWorkItem(id);
    if (item == nullptr)
    {
        std::cout << "  [TIVIDY] No work item with id " << id << std::endl;
    }
    return item;
}

int TIVIDY::createWorkItem(const std::string& name, int deadline)
{
    AbstractWorkItem* item = new WorkItem(nextId++, name, deadline, mediator);
    mediator->addWorkItem(item);
    std::cout << "  [TIVIDY] Created '" << name << "' (id " << item->getId() << ")" << std::endl;
    return item->getId();
}

void TIVIDY::advanceWork(int id)
{
    AbstractWorkItem* item = find(id);
    if (item != nullptr)
    {
        item->handleState();
    }
}

void TIVIDY::submitWork(int id, const std::string& data)
{
    AbstractWorkItem* item = find(id);
    if (item != nullptr)
    {
        item->set(data);
        item->handleState();
    }
}

void TIVIDY::pauseWork(int id)
{
    AbstractWorkItem* item = find(id);
    if (item != nullptr)
    {
        item->paused();
    }
}

void TIVIDY::resumeWork(int id)
{
    AbstractWorkItem* item = find(id);
    if (item != nullptr)
    {
        item->resume();
    }
}

bool TIVIDY::addDependency(int predecessorId, int successorId)
{
    return mediator->addDependency(predecessorId, successorId);
}

std::string TIVIDY::getWorkItemState(int id) const
{
    AbstractWorkItem* item = find(id);
    return item != nullptr ? item->getStateName() : "";
}

void TIVIDY::printStatus() const
{
    std::cout << "  [TIVIDY] Work items:" << std::endl;
    for (AbstractWorkItem* item : mediator->getWorkItems())
    {
        std::cout << "    " << item->getId() << " " << item->getName() << ": " << item->getStateName() << std::endl;
    }
}

void TIVIDY::runWorkflow(AbstractWorkflowFactory* factory){
    if (factory == nullptr)
    {
        std::cout << "  [TIVIDY] Cannot run a null workflow factory." << std::endl;
        return;
    }

    //basically using same factory create products A and B...

    AbstractWorkflowInstanceA* instanceA = factory->createWorkflowInstanceA();

    AbstractWorkflowInstanceB* instanceB = factory->createWorkflowInstanceB();

    instanceA->create();
    instanceB->create();

    delete instanceA;
    delete instanceB;
}
