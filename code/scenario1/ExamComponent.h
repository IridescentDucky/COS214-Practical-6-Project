#ifndef EXAMCOMPONENT_H
#define EXAMCOMPONENT_H

class ExamComponent {
public:
    virtual ~ExamComponent() = default;
    virtual double getBonusMarks() = 0;
    virtual int getExtraTime() = 0;

};

#endif
