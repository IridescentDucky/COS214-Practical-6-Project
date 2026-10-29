#include "ExamPaperCollection.h"
#include "ExamPaperIterator.h"
#include "AbstractExamPaper.h"

#include <algorithm>
#include <iostream>

ExamPaperCollection::~ExamPaperCollection() {

}

void ExamPaperCollection::addPaper(AbstractExamPaper* paper) {
    
    if (paper != nullptr) {
        std::cout << "[ExamPaperCollection] Paper added to collection." << std::endl;
        papers.push_back(paper);
    }
}

void ExamPaperCollection::removePaper(AbstractExamPaper* paper) {
    
    std::vector<AbstractExamPaper*>::iterator it = std::find(papers.begin(), papers.end(), paper);
    if (it != papers.end()) {
        papers.erase(it);
        std::cout << "[ExamPaperCollection] Paper removed from collection." << std::endl;
    }
}

Iterator* ExamPaperCollection::createIterator() {
    
    return new ExamPaperIterator(this);
}

AbstractExamPaper* ExamPaperCollection::getPaperAt(int index) const {
    
    if (index >= 0 && static_cast<std::size_t>(index) < papers.size()) {
        return papers[static_cast<std::size_t>(index)];
    }
    return nullptr;
}

int ExamPaperCollection::getSize() const {
    
    return static_cast<int>(papers.size());
}
