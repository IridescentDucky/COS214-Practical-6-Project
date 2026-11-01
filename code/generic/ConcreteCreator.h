#ifndef CONCRETECREATOR_H
#define CONCRETECREATOR_H

#include "Creator.h"

/** @brief Creates concrete WorkItem instances through the Creator interface. */
template <typename T>
class ConcreteCreator : public Creator<T> {
protected:
    /** @brief Constructs a concrete work item.
     *  @param id Work-item identifier.
     *  @param name Work-item name.
     *  @param deadline Allowed work duration.
     *  @param mediator Mediator coordinating the work item.
     *  @return The newly created work item.
     */
    AbstractWorkItem<T>* factoryMethod(int id, const std::string& name, int deadline, WorkflowMediator<T>* mediator);
};

#endif