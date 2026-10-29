#ifndef AGGREGATE_H
#define AGGREGATE_H

class Iterator;

class Aggregate {
    
public:
    virtual ~Aggregate() = default;
    virtual Iterator* createIterator() = 0;
};

#endif
