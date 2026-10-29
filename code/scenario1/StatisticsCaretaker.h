#ifndef STATISTICSCARETAKER_H
#define STATISTICSCARETAKER_H

class StatisticsMemento;

class StatisticsCaretaker{
    
private:
    StatisticsMemento* memento;

public:
    StatisticsCaretaker();
    ~StatisticsCaretaker();

    StatisticsMemento* getMemento() const;
    void saveMemento(StatisticsMemento* memento);
};

#endif
