#ifndef EXAMPAPERCREATOR_H
#define EXAMPAPERCREATOR_H

#include "Creator.h"

class ExamPaperCreator : public Creator {
protected:
    AbstractExamPaper* factoryMethod(
        const std::string& moduleCode,
        int examDuration,
        double marks,
        int year) override;
};

#endif
