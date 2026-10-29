#ifndef EXAMCOMPONENT_H
#define EXAMCOMPONENT_H

class ExamComponent {
public:
    virtual ~ExamComponent() = default;
    virtual void mark();
    virtual double getMarks();

};

#endif
