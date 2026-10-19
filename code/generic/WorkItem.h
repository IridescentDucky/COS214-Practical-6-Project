#ifndef WORKITEM_H
#define WORKITEM_H

#include <string>

class WorkItemState;
class WorkflowMediator;

class AbstractWorkItem
{
public:
    AbstractWorkItem(int id, const std::string& name, WorkflowMediator* mediator);
    virtual ~AbstractWorkItem();

    int getId() const;
    std::string getName() const;
    std::string getStateName() const;

    virtual void handleState() = 0;
    virtual void paused() = 0;
    virtual void resume() = 0;
    virtual void retry() = 0;
    virtual void failed() = 0;
    virtual void failedDelivery() = 0;
    virtual void exception() = 0;
    virtual void validate() = 0;

    virtual void set(const std::string& data) = 0;
    virtual std::string get() const = 0;
    virtual void addTimeSpent(int units) = 0;

protected:
    int id;
    std::string name;
    WorkItemState* state;
    WorkflowMediator* mediator;
};

class WorkItem : public AbstractWorkItem
{
public:
    WorkItem(int id, const std::string& name, int deadline, WorkflowMediator* mediator);

    void handleState() override;
    void paused() override;
    void resume() override;
    void retry() override;
    void failed() override;
    void failedDelivery() override;
    void exception() override;
    void validate() override;

    void set(const std::string& data) override;
    std::string get() const override;
    void addTimeSpent(int units) override;

    WorkItemState* getState() const;
    void setState(WorkItemState* newState);

    bool isWithinDeadline() const;
    bool hasValidData() const;
    void notifyWorkflow();

private:
    std::string data;
    int deadline;
    int timeSpent;
};

#endif
