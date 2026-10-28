#ifndef STATE_H
#define STATE_H

#include <string>

class WorkItem;

//workitemstate
class WorkItemState
{
public:
    virtual ~WorkItemState()
    {
    }
    virtual std::string getName() const = 0;
    virtual WorkItemState* clone() const = 0;

    virtual void nextState(WorkItem* item);
    virtual void paused(WorkItem* item);
    virtual void resume(WorkItem* item);
    virtual void retry(WorkItem* item);
    virtual void failed(WorkItem* item);
    virtual void failedDelivery(WorkItem* item);
    virtual void exception(WorkItem* item);
    virtual void validate(WorkItem* item);

protected:
    void reject(const std::string& operation) const;
};

//created
class Created : public WorkItemState
{
public:
    std::string getName() const override;
    WorkItemState* clone() const override;
    void nextState(WorkItem* item) override;
};

//delivered
class Delivered : public WorkItemState
{
public:
    std::string getName() const override;
    WorkItemState* clone() const override;
    void nextState(WorkItem* item) override;
    void failedDelivery(WorkItem* item) override;
    void retry(WorkItem* item) override;
};

//inprogress
class InProgress : public WorkItemState
{
public:
    std::string getName() const override;
    WorkItemState* clone() const override;
    void nextState(WorkItem* item) override;
    void paused(WorkItem* item) override;
    void failed(WorkItem* item) override;
    void exception(WorkItem* item) override;
};

//paused
class Paused : public WorkItemState
{
public:
    std::string getName() const override;
    WorkItemState* clone() const override;
    void nextState(WorkItem* item) override;
    void resume(WorkItem* item) override;
};

//completed
class Completed : public WorkItemState
{
public:
    std::string getName() const override;
    WorkItemState* clone() const override;
    void nextState(WorkItem* item) override;
};

//validation
class Validation : public WorkItemState
{
public:
    std::string getName() const override;
    WorkItemState* clone() const override;
    void nextState(WorkItem* item) override;
    void retry(WorkItem* item) override;
    void failed(WorkItem* item) override;
};

//failed
class Failed : public WorkItemState
{
public:
    std::string getName() const override;
    WorkItemState* clone() const override;
    void nextState(WorkItem* item) override;
};

//archived
class Archived : public WorkItemState
{
public:
    std::string getName() const override;
    WorkItemState* clone() const override;
    void nextState(WorkItem* item) override;
};

//exception
class Exception : public WorkItemState
{
public:
    std::string getName() const override;
    WorkItemState* clone() const override;
    void nextState(WorkItem* item) override;
    void validate(WorkItem* item) override;
};

#endif
