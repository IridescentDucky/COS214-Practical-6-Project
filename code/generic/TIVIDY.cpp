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

void TIVIDY::printStatus() const
{
    std::cout << "  [TIVIDY] Work items:" << std::endl;
    for (AbstractWorkItem* item : mediator->getWorkItems())
    {
        std::cout << "    " << item->getId() << " " << item->getName() << ": " << item->getStateName() << std::endl;
    }
}
