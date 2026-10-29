#ifndef EXAMPAPERCOLLECTION_H
#define EXAMPAPERCOLLECTION_H

#include <vector>
#include "Aggregate.h"

class AbstractExamPaper;
class Iterator;

class ExamPaperCollection : public Aggregate {
    
private:
    std::vector<AbstractExamPaper*> papers;
    
public:
    
    ExamPaperCollection() = default;
    virtual ~ExamPaperCollection();
    
    void addPaper(AbstractExamPaper* paper);
    void removePaper(AbstractExamPaper* paper);
    Iterator* createIterator();
    
    AbstractExamPaper* getPaperAt(int index) const;
    int getSize() const;
};

#endif
