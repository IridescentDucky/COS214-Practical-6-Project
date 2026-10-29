#ifndef EXAMDELIVERY_H
#define EXAMDELIVERY_H

#include "ExamDeliveryService.h"

class ExamDelivery : public ExamDeliveryService {
public:
    explicit ExamDelivery(AbstractExamPaper* paper);
    void attach(Marker* marker) override;
    void detach(Marker* marker) override;
    void notify() override;
    AbstractExamPaper* getExamPaper() override;
};

#endif
