#ifndef STATSCARETAKER_H
#define STATSCARETAKER_H

class StatsMemento;

class StatsCaretaker{
    
private:
    StatsMemento* memento;

public:
    StatsCaretaker();
    ~StatsCaretaker();

    StatsMemento* getMemento() const;
    void saveMemento(StatsMemento* m);
};

#endif
