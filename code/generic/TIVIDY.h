#ifndef TIVIDY_H
#define TIVIDY_H

#include <string>

class AbstractWorkItem;
class WorkflowMediator;

class TIVIDY
{
public:
    TIVIDY();
    ~TIVIDY();
    TIVIDY(const TIVIDY&) = delete;
    TIVIDY& operator=(const TIVIDY&) = delete;

    int createWorkItem(const std::string& name, int deadline);
    void advanceWork(int id);
    void submitWork(int id, const std::string& data);
    void pauseWork(int id);
    void resumeWork(int id);
    void printStatus() const;

private:
    AbstractWorkItem* find(int id) const;

    WorkflowMediator* mediator;
    int nextId;
};

#endif
