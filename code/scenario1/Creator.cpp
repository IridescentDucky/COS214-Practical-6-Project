#include "Creator.h"

AbstractExamPaper* Creator::createExamPaper(
    const std::string& moduleCode,
    int examDuration,
    double marks,int year) {
    return factoryMethod(moduleCode, examDuration, marks,year);
}
