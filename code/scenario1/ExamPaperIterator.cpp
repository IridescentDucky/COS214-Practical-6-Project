#include "ExamPaperIterator.h"
#include "ExamPaperCollection.h"
#include "ExamPaper.h"
#include <iostream>

ExamPaperIterator::ExamPaperIterator(ExamPaperCollection* col)
    : currentIndex(0), collection(col) {}

bool ExamPaperIterator::hasNext() {
    
    if (collection == nullptr) {
        return false;
    }
    
    bool res = currentIndex < collection->getSize();
    std::cout << "[ExamPaperIterator] hasNext(): " << (res ? "true" : "false") << std::endl;
    return res;
}

ExamPaper* ExamPaperIterator::next() {
    
    if (!hasNext()) {
        std::cout << "[ExamPaperIterator] No more elements." << std::endl;
        return nullptr;
    }

    AbstractExamPaper* abstractPaper = collection->getPaperAt(currentIndex);
    currentIndex++;

    std::cout << "[ExamPaperIterator] next paper: " << abstractPaper->getModuleCode() << std::endl;
    return dynamic_cast<ExamPaper*>(abstractPaper);
}
