#ifndef EXAMPAPERGROUP_H
#define EXAMPAPERGROUP_H

#include "ExamComponent.h"

#include <vector>

class ExamPaperGroup : public ExamComponent {
private:
    std::vector<ExamComponent*> elements;

public:
    void mark();
    void add(ExamComponent* element);
    void remove(ExamComponent* element);
    double getMarks();
    double getBonusMarks() override;
    int getExtraTime() override;
};

#endif