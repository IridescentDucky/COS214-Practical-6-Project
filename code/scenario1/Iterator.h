#ifndef ITERATOR_H
#define ITERATOR_H

class ExamPaper;

class Iterator{
    
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() = 0;
    virtual ExamPaper* next() = 0;
};

#endif
