#ifndef STATSMEMENTO_H
#define STATSMEMENTO_H

/** @brief Immutable snapshot of the statistics originator's state. */
class StatsMemento {
    
private:
    int year;
    double maxMark;
    double minMark;
    double scoreAvg;
    
public:
    /** @brief Captures a statistics snapshot.
     *  @param y Year associated with the statistics.
     *  @param max Highest mark.
     *  @param min Lowest mark.
     *  @param sAvg Average score.
     */
    StatsMemento(int y, double max, double min, double sAvg): year(y), maxMark(max), minMark(min), scoreAvg(sAvg) {}
    
    /** @brief Gets the snapshot year. */
    int getYear() const { return year; }
    /** @brief Gets the highest mark in the snapshot. */
    double getMaxMark() const { return maxMark; }
    /** @brief Gets the lowest mark in the snapshot. */
    double getMinMark() const { return minMark; }
    /** @brief Gets the average score in the snapshot. */
    double getScoreAvg() const { return scoreAvg;}
};

#endif
