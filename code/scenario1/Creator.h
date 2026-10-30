#ifndef CREATOR_H
#define CREATOR_H

#include "AbstractExamPaper.h"

#include <string>

class Creator {
public:
    virtual ~Creator() = default;
    AbstractExamPaper* createExamPaper(
        const std::string& moduleCode,
        int examDuration,
        double marks, int year);    //added year param so Mememento has that

protected:
    virtual AbstractExamPaper* factoryMethod(
        const std::string& moduleCode,
        int examDuration,
        double marks, int year) = 0;        //do we need string&?
};    

#endif
