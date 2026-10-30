#ifndef EXTRAMARKSDECORATOR_H
#define EXTRAMARKSDECORATOR_H

#include "ExamDecorator.h"

class ExtraMarksDecorator : public ExamDecorator {
private:
    double extraMarks;

public:
    ExtraMarksDecorator(ExamComponent* component, double extraMarks);
    double getBonusMarks();
};

#endif
