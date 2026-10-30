#include "State.h"
#include "WorkItem.h"

#include <iostream>

//State
template <typename T>
void State<T>::reject(const std::string& operation) const
{
    std::cout << "  [State] '" << operation << "' is not allowed while " << getName() << std::endl;
}

template <typename T>
void State<T>::nextState(WorkItem<T>*)
{
    State<T>::reject("nextState");
}

template <typename T>
void State<T>::paused(WorkItem<T>*)
{
    State<T>::reject("paused");
}

template <typename T>
void State<T>::resume(WorkItem<T>*)
{
    State<T>::reject("resume");
}

template <typename T>
void State<T>::retry(WorkItem<T>*)
{
    State<T>::reject("retry");
}

template <typename T>
void State<T>::failed(WorkItem<T>*)
{
    State<T>::reject("failed");
}

template <typename T>
void State<T>::failedDelivery(WorkItem<T>*)
{
    State<T>::reject("failedDelivery");
}

template <typename T>
void State<T>::exception(WorkItem<T>*)
{
    State<T>::reject("exception");
}

template <typename T>
void State<T>::validate(WorkItem<T>*)
{
    State<T>::reject("validate");
}

//created
template <typename T>
std::string Created<T>::getName() const
{
    return "Created";
}

template <typename T>
State<T>* Created<T>::clone() const
{
    return new Created<T>();
}

template <typename T>
void Created<T>::nextState(WorkItem<T>* item)
{
    item->setState(new Delivered<T>());
}

//delivered
template <typename T>
std::string Delivered<T>::getName() const
{
    return "Delivered";
}

template <typename T>
State<T>* Delivered<T>::clone() const
{
    return new Delivered();
}

template <typename T>
void Delivered<T>::nextState(WorkItem<T>* item)
{
    item->setState(new InProgress<T>());
}

template <typename T>
void Delivered<T>::failedDelivery(WorkItem<T>* item)
{
    item->setState(new Failed<T>());
}

template <typename T>
void Delivered<T>::retry(WorkItem<T>* item)
{
    item->setState(new Delivered<T>());
}

//inprogress
template <typename T>
std::string InProgress<T>::getName() const
{
    return "InProgress";
}

template <typename T>
State<T>* InProgress<T>::clone() const
{
    return new InProgress<T>();
}

template <typename T>
void InProgress<T>::nextState(WorkItem<T>* item)
{
    if (item->isWithinDeadline())
    {
        item->setState(new Validation<T>());
    }
    else
    {
        std::cout << "  [State] guard [withinDeadline] failed for " << item->getName() << std::endl;
    }
}

template <typename T>
void InProgress<T>::paused(WorkItem<T>* item)
{
    item->setState(new Paused<T>());
}

template <typename T>
void InProgress<T>::failed(WorkItem<T>* item)
{
    item->setState(new Failed<T>());
}

template <typename T>
void InProgress<T>::exception(WorkItem<T>* item)
{
    item->setState(new Exception<T>());
}

//paused
template <typename T>
std::string Paused<T>::getName() const
{
    return "Paused";
}

template <typename T>
State<T>* Paused<T>::clone() const
{
    return new Paused<T>();
}

template <typename T>
void Paused<T>::nextState(WorkItem<T>* item)
{
    resume(item);
}

template <typename T>
void Paused<T>::resume(WorkItem<T>* item)
{
    item->setState(new InProgress<T>());
}

//completed
template <typename T>
std::string Completed<T>::getName() const
{
    return "Completed";
}

template <typename T>
State<T>* Completed<T>::clone() const
{
    return new Completed<T>();
}

template <typename T>
void Completed<T>::nextState(WorkItem<T>* item)
{
    item->setState(new Archived<T>());
}

//validation
template <typename T>
std::string Validation<T>::getName() const
{
    return "Validation";
}

template <typename T>
State<T>* Validation<T>::clone() const
{
    return new Validation<T>();
}

template <typename T>
void Validation<T>::nextState(WorkItem<T>* item)
{
    if (item->hasValidData())
    {
        item->setState(new Completed<T>());
        item->notifyWorkflow();
    }
    else
    {
        item->setState(new InProgress<T>());
    }
}

template <typename T>
void Validation<T>::retry(WorkItem<T>* item)
{
    item->setState(new InProgress<T>());
}

template <typename T>
void Validation<T>::failed(WorkItem<T>* item)
{
    item->setState(new Failed<T>());
}

//failed
template <typename T>
std::string Failed<T>::getName() const
{
    return "Failed";
}

template <typename T>
State<T>* Failed<T>::clone() const
{
    return new Failed();
}

template <typename T>
void Failed<T>::nextState(WorkItem<T>* item)
{
    item->setState(new Archived<T>());
}

//archived
template <typename T>
std::string Archived<T>::getName() const
{
    return "Archived";
}

template <typename T>
State<T>* Archived<T>::clone() const
{
    return new Archived<T>();
}

template <typename T>
void Archived<T>::nextState(WorkItem<T>*)
{
    State<T>::reject("nextState");
}

//exception
template <typename T>
std::string Exception<T>::getName() const
{
    return "Exception";
}

template <typename T>
State<T>* Exception<T>::clone() const
{
    return new Exception<T>();
}


template <typename T>
void Exception<T>::nextState(WorkItem<T>* item)
{
    item->setState(new InProgress<T>());
}


template <typename T>
void Exception<T>::validate(WorkItem<T>* item)
{
    item->setState(new Validation<T>());
}

template class State<int>;
template class Created<int>;
template class Delivered<int>;
template class InProgress<int>;
template class Paused<int>;
template class Completed<int>;
template class Validation<int>;
template class Failed<int>;
template class Archived<int>;
template class Exception<int>;
