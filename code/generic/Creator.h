#ifndef CREATOR_H
#define CREATOR_H

#include "AbstractWorkItem.h"

/** @brief Factory-method base that creates and registers work items. */
template <typename T>
class Creator {
public:
    /** @brief Destroys the creator through its base interface. */
    virtual ~Creator();
    /** @brief Creates a work item using the concrete factory method.
     *  @param id Work-item identifier.
     *  @param name Work-item name.
     *  @param deadline Allowed work duration.
     *  @param mediator Mediator coordinating the work item.
     *  @return The newly created work item.
     */
    AbstractWorkItem<T>* createWorkItem(int id, const std::string& name, int deadline, WorkflowMediator<T>* mediator); //followed Chocolate example in lecture slides

protected:
    /** @brief Constructs the concrete work-item type.
     *  @param id Work-item identifier.
     *  @param name Work-item name.
     *  @param deadline Allowed work duration.
     *  @param mediator Mediator coordinating the work item.
     *  @return The newly created work item.
     */
    virtual AbstractWorkItem<T>* factoryMethod(int id, const std::string& name, int deadline, WorkflowMediator<T>* mediator) = 0;

// private:
//     AbstractWorkItem* item; //note we dont really need this, we arent using it anywhere

};

#endif