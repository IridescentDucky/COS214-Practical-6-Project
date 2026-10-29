#include "Creator.h"

AbstractExamPaper* Creator::createExamPaper(
    const std::string& moduleCode,
    int examDuration,
    double marks) {
    return factoryMethod(moduleCode, examDuration, marks);
}
