#ifndef EXAMPAPERITERATOR_H
#define EXAMPAPERITERATOR_H

#include "Iterator.h"

class ExamPaperCollection;
class ExamPaper;

class ExamPaperIterator: public Iterator{
    
private:
    int currentIndex;
    ExamPaperCollection* collection;
    
public:
    ExamPaperIterator(ExamPaperCollection* col);
    virtual ~ExamPaperIterator() override = default;
    
    virtual bool hasNext() override;
    virtual ExamPaper* next() override;
};

#endif
