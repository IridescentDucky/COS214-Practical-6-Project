#include "AverageMarksStrategy.h"

#include "ExamPaper.h"

ExamMetricResult AverageMarksStrategy::calculateStats(const ExamPaper& paper) const {
    ExamMetricResult result;
    result.metric = ExamMetric::MarksPerAllocatedMinute;
    result.metricName = getExamMetricName(result.metric);
    result.moduleCode = paper.getModuleCode();

    if (paper.getExamDuration() <= 0 || !paper.isMarked()) {
        return result;
    }

    result.value = paper.getMarks() / paper.getExamDuration();
    result.valid = true;
    return result;
}
