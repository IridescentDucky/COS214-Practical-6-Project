#include "WorkItem.h"
#include "State.h"
#include "WorkflowMediator.h"

#include <iostream>

AbstractWorkItem::AbstractWorkItem(int id, const std::string& name, WorkflowMediator* mediator)
    : id(id), name(name), state(new Created()), mediator(mediator)
{
}

AbstractWorkItem::~AbstractWorkItem()
{
    delete state;
}

int AbstractWorkItem::getId() const
{
    return id;
}

std::string AbstractWorkItem::getName() const
{
    return name;
}

std::string AbstractWorkItem::getStateName() const
{
    return state->getName();
}

WorkItem::WorkItem(int id, const std::string& name, int deadline, WorkflowMediator* mediator)
    : AbstractWorkItem(id, name, mediator), deadline(deadline), timeSpent(0)
{
}

void WorkItem::handleState()
{
    state->nextState(this);
}

void WorkItem::paused()
{
    state->paused(this);
}

void WorkItem::resume()
{
    state->resume(this);
}

void WorkItem::retry()
{
    state->retry(this);
}

void WorkItem::failed()
{
    state->failed(this);
}

void WorkItem::failedDelivery()
{
    state->failedDelivery(this);
}

void WorkItem::exception()
{
    state->exception(this);
}

void WorkItem::validate()
{
    state->validate(this);
}

void WorkItem::set(const std::string& data)
{
    this->data = data;
}

std::string WorkItem::get() const
{
    return data;
}

void WorkItem::addTimeSpent(int units)
{
    timeSpent += units;
}

WorkItemState* WorkItem::getState() const
{
    return state;
}

void WorkItem::setState(WorkItemState* newState)
{
    std::cout << "  [State] " << name << ": " << state->getName() << " -> " << newState->getName() << std::endl;
    WorkItemState* old = state;
    state = newState;
    delete old;
}

bool WorkItem::isWithinDeadline() const
{
    return timeSpent <= deadline;
}

bool WorkItem::hasValidData() const
{
    return !data.empty();
}

void WorkItem::notifyWorkflow()
{
    mediator->notify(this);
}
