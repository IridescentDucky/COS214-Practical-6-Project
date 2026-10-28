#ifndef EXAMPAPERGROUP_H
#define EXAMPAPERGROUP_H

#include "ExamComponent.h"

#include <iostream>
#include <list>

using namespace std;

class ExamPaperGroup : ExamComponent {
private:
    list<ExamComponent*> elements;

public:
    void mark();
    void add(ExamComponent* e);
    void remove(ExamComponent* e);

    // getchild?
};

#endif