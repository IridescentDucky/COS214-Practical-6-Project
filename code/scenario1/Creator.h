#ifndef CREATOR_H
#define CREATOR_H

#include "AbstractExamPaper.h"

class Creator {
public:
    virtual ~Creator() = default;
    AbstractExamPaper* createExamPaper(
        const std::string& moduleCode,
        int examDuration,
        double marks);

protected:
    virtual AbstractExamPaper* factoryMethod(
        const std::string& moduleCode,
        int examDuration,
        double marks) = 0;
};

#endif
