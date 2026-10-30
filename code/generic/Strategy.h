#ifndef STRATEGY_H
#define STRATEGY_H

template <typename T>
class AbstractWorkItem;

template <typename T>
class Strategy {
    
public:
    virtual ~Strategy() = default;
    virtual double algorithm(AbstractWorkItem<T>* item) = 0;
};

#endif
