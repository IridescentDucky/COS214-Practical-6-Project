#ifndef EXAMCOMPONENT_H
#define EXAMCOMPONENT_H

class ExamComponent {
public:
    virtual void mark() = 0;
    virtual double getMarks() = 0;

    virtual void add(ExamComponent* e);
    virtual void remove(ExamComponent* e);
};

#endif