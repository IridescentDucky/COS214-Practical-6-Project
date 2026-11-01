#ifndef STATSCARETAKER_H
#define STATSCARETAKER_H

class StatsMemento;

class StatsCaretaker{
    
private:
    StatsMemento* memento;

public:
    StatsCaretaker();
    ~StatsCaretaker();
    StatsCaretaker(const StatsCaretaker&) = delete;
    StatsCaretaker& operator=(const StatsCaretaker&) = delete;

    StatsMemento* getMemento() const;
    void saveMemento(StatsMemento* m);
};

#endif
