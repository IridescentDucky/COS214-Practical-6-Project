#ifndef EXAMRESULTSSTRATEGY_H
#define EXAMRESULTSSTRATEGY_H

#include <string>

class ExamPaper;

enum class ExamMetric {
    TopQuestion,
    LowestQuestion,
    MarksPerAllocatedMinute
};

inline const char* getExamMetricName(ExamMetric metric) {
    switch (metric) {
    case ExamMetric::TopQuestion:
        return "Top question percentage";
    case ExamMetric::LowestQuestion:
        return "Lowest question percentage";
    case ExamMetric::MarksPerAllocatedMinute:
        return "Marks per allocated minute";
    }
    return "Unknown exam metric";
}

struct ExamMetricResult {
    ExamMetric metric;
    std::string metricName;
    std::string moduleCode;
    std::string question;
    double value;
    bool valid;

    ExamMetricResult()
        : metric(ExamMetric::TopQuestion),
          metricName(getExamMetricName(ExamMetric::TopQuestion)),
          value(0.0),
          valid(false) {}
};

class ExamResultsStrategy {
public:
    virtual ~ExamResultsStrategy() = default;
    virtual ExamMetricResult calculateStats(const ExamPaper& paper) const = 0;
};

#endif
