#ifndef STATE_H
#define STATE_H

#include <string>

template <typename T>
class WorkItem;

//workitemstate
template <typename T>
class WorkItemState
{
public:
    virtual ~WorkItemState()
    {
    }
    virtual std::string getName() const = 0;
    virtual WorkItemState<T>* clone() const = 0;

    virtual void nextState(WorkItem<T>* item);
    virtual void paused(WorkItem<T>* item);
    virtual void resume(WorkItem<T>* item);
    virtual void retry(WorkItem<T>* item);
    virtual void failed(WorkItem<T>* item);
    virtual void failedDelivery(WorkItem<T>* item);
    virtual void exception(WorkItem<T>* item);
    virtual void validate(WorkItem<T>* item);

protected:
    void reject(const std::string& operation) const;
};

//created
template <typename T>
class Created : public WorkItemState<T>
{
public:
    std::string getName() const override;
    WorkItemState<T>* clone() const override;
    void nextState(WorkItem<T>* item) override;
};

//delivered
template <typename T>
class Delivered : public WorkItemState<T>
{
public:
    std::string getName() const override;
    WorkItemState<T>* clone() const override;
    void nextState(WorkItem<T>* item) override;
    void failedDelivery(WorkItem<T>* item) override;
    void retry(WorkItem<T>* item) override;
};

//inprogress
template <typename T>
class InProgress : public WorkItemState<T>
{
public:
    std::string getName() const override;
    WorkItemState<T>* clone() const override;
    void nextState(WorkItem<T>* item) override;
    void paused(WorkItem<T>* item) override;
    void failed(WorkItem<T>* item) override;
    void exception(WorkItem<T>* item) override;
};

//paused
template <typename T>
class Paused : public WorkItemState<T>
{
public:
    std::string getName() const override;
    WorkItemState<T>* clone() const override;
    void nextState(WorkItem<T>* item) override;
    void resume(WorkItem<T>* item) override;
};

//completed
template <typename T>
class Completed : public WorkItemState<T>
{
public:
    std::string getName() const override;
    WorkItemState<T>* clone() const override;
    void nextState(WorkItem<T>* item) override;
};

//validation
template <typename T>
class Validation : public WorkItemState<T>
{
public:
    std::string getName() const override;
    WorkItemState<T>* clone() const override;
    void nextState(WorkItem<T>* item) override;
    void retry(WorkItem<T>* item) override;
    void failed(WorkItem<T>* item) override;
};

//failed
template <typename T>
class Failed : public WorkItemState<T>
{
public:
    std::string getName() const override;
    WorkItemState<T>* clone() const override;
    void nextState(WorkItem<T>* item) override;
};

//archived
template <typename T>
class Archived : public WorkItemState<T>
{
public:
    std::string getName() const override;
    WorkItemState<T>* clone() const override;
    void nextState(WorkItem<T>* item) override;
};

//exception
template <typename T>
class Exception : public WorkItemState<T>
{
public:
    std::string getName() const override;
    WorkItemState<T>* clone() const override;
    void nextState(WorkItem<T>* item) override;
    void validate(WorkItem<T>* item) override;
};

#endif
