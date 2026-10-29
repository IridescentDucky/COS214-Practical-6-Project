#ifndef EXAMDELIVERYSERVICE_H
#define EXAMDELIVERYSERVICE_H

#include <vector>

class AbstractExamPaper;
class Marker;

class ExamDeliveryService {
protected:
    std::vector<Marker*> markerObservers;
    AbstractExamPaper* examPaper;

    explicit ExamDeliveryService(AbstractExamPaper* paper);

public:
    virtual ~ExamDeliveryService() = default;
    virtual void attach(Marker* marker) = 0;
    virtual void detach(Marker* marker) = 0;
    virtual void notify() = 0;
    virtual AbstractExamPaper* getExamPaper() = 0;
};

#endif
