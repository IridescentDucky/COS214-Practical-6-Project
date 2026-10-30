#include "ExamPaperCreator.h"

#include "ExamPaper.h"

AbstractExamPaper* ExamPaperCreator::factoryMethod(
    const std::string& moduleCode,
    int examDuration,
    double marks) {
    return new ExamPaper(moduleCode, examDuration, marks);
}
