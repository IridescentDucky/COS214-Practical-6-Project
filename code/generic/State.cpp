#include "State.h"
#include "WorkItem.h"

#include <iostream>

//workitemstate
void WorkItemState::reject(const std::string& operation) const
{
    std::cout << "  [State] '" << operation << "' is not allowed while " << getName() << std::endl;
}

void WorkItemState::nextState(WorkItem*)
{
    reject("nextState");
}

void WorkItemState::paused(WorkItem*)
{
    reject("paused");
}

void WorkItemState::resume(WorkItem*)
{
    reject("resume");
}

void WorkItemState::retry(WorkItem*)
{
    reject("retry");
}

void WorkItemState::failed(WorkItem*)
{
    reject("failed");
}

void WorkItemState::failedDelivery(WorkItem*)
{
    reject("failedDelivery");
}

void WorkItemState::exception(WorkItem*)
{
    reject("exception");
}

void WorkItemState::validate(WorkItem*)
{
    reject("validate");
}

//created
std::string Created::getName() const
{
    return "Created";
}

void Created::nextState(WorkItem* item)
{
    item->setState(new Delivered());
}

//delivered
std::string Delivered::getName() const
{
    return "Delivered";
}

void Delivered::nextState(WorkItem* item)
{
    item->setState(new InProgress());
}

void Delivered::failedDelivery(WorkItem* item)
{
    item->setState(new Failed());
}

void Delivered::retry(WorkItem* item)
{
    item->setState(new Delivered());
}

//inprogress
std::string InProgress::getName() const
{
    return "InProgress";
}

void InProgress::nextState(WorkItem* item)
{
    if (item->isWithinDeadline())
    {
        item->setState(new Validation());
    }
    else
    {
        std::cout << "  [State] guard [withinDeadline] failed for " << item->getName() << std::endl;
    }
}

void InProgress::paused(WorkItem* item)
{
    item->setState(new Paused());
}

void InProgress::failed(WorkItem* item)
{
    item->setState(new Failed());
}

void InProgress::exception(WorkItem* item)
{
    item->setState(new Exception());
}

//paused
std::string Paused::getName() const
{
    return "Paused";
}

void Paused::nextState(WorkItem* item)
{
    resume(item);
}

void Paused::resume(WorkItem* item)
{
    item->setState(new InProgress());
}

//completed
std::string Completed::getName() const
{
    return "Completed";
}

void Completed::nextState(WorkItem* item)
{
    item->setState(new Archived());
}

//validation
std::string Validation::getName() const
{
    return "Validation";
}

void Validation::nextState(WorkItem* item)
{
    if (item->hasValidData())
    {
        item->setState(new Completed());
        item->notifyWorkflow();
    }
    else
    {
        item->setState(new InProgress());
    }
}

void Validation::retry(WorkItem* item)
{
    item->setState(new InProgress());
}

void Validation::failed(WorkItem* item)
{
    item->setState(new Failed());
}

//failed
std::string Failed::getName() const
{
    return "Failed";
}

void Failed::nextState(WorkItem* item)
{
    item->setState(new Archived());
}

//archived
std::string Archived::getName() const
{
    return "Archived";
}

void Archived::nextState(WorkItem*)
{
    reject("nextState");
}

//exception
std::string Exception::getName() const
{
    return "Exception";
}

void Exception::nextState(WorkItem* item)
{
    item->setState(new InProgress());
}

void Exception::validate(WorkItem* item)
{
    item->setState(new Validation());
}
