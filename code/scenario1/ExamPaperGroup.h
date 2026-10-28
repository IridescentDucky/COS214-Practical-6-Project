#ifndef EXAMPAPERGROUP_H
#define EXAM PAPERGROUP_H

#include "ExamComponent.h"

#include <vector>
#include <iostream>

using namespace std;

class ExamPaperGroup : ExamComponent {
private:
    vector<ExamComponent*> elements;

public:
    void mark();
    double getMarks();

    void add(ExamComponent* e);
    void remove(ExamComponent* e);
};

#endif