#ifndef STATE_H
#define STATE_H

#include <string>

template <typename T>
class WorkItem;

template <typename T>
class State {
public:
    virtual ~State() {}
    
    virtual std::string getName() const = 0;
    virtual State<T>* clone() const = 0;

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
class Created : public State<T>
{
public:
    std::string getName() const override;
    State<T>* clone() const override;
    void nextState(WorkItem<T>* item) override;
};

//delivered
template <typename T>
class Delivered : public State<T>
{
public:
    std::string getName() const override;
    State<T>* clone() const override;
    void nextState(WorkItem<T>* item) override;
    void failedDelivery(WorkItem<T>* item) override;
    void retry(WorkItem<T>* item) override;
};

//inprogress
template <typename T>
class InProgress : public State<T>
{
public:
    std::string getName() const override;
    State<T>* clone() const override;
    void nextState(WorkItem<T>* item) override;
    void paused(WorkItem<T>* item) override;
    void failed(WorkItem<T>* item) override;
    void exception(WorkItem<T>* item) override;
};

//paused
template <typename T>
class Paused : public State<T>
{
public:
    std::string getName() const override;
    State<T>* clone() const override;
    void nextState(WorkItem<T>* item) override;
    void resume(WorkItem<T>* item) override;
};

//completed
template <typename T>
class Completed : public State<T>
{
public:
    std::string getName() const override;
    State<T>* clone() const override;
    void nextState(WorkItem<T>* item) override;
};

//validation
template <typename T>
class Validation : public State<T>
{
public:
    std::string getName() const override;
    State<T>* clone() const override;
    void nextState(WorkItem<T>* item) override;
    void retry(WorkItem<T>* item) override;
    void failed(WorkItem<T>* item) override;
};

//failed
template <typename T>
class Failed : public State<T>
{
public:
    std::string getName() const override;
    State<T>* clone() const override;
    void nextState(WorkItem<T>* item) override;
};

//archived
template <typename T>
class Archived : public State<T>
{
public:
    std::string getName() const override;
    State<T>* clone() const override;
    void nextState(WorkItem<T>* item) override;
};

//exception
template <typename T>
class Exception : public State<T>
{
public:
    std::string getName() const override;
    State<T>* clone() const override;
    void nextState(WorkItem<T>* item) override;
    void validate(WorkItem<T>* item) override;
};

#endif
