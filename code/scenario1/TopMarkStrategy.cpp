#include "TopMarkStrategy.h"

#include "ExamPaper.h"

ExamMetricResult TopMarkStrategy::calculateStats(const ExamPaper& paper) const {
    ExamMetricResult result;
    result.metric = ExamMetric::TopQuestion;
    result.metricName = getExamMetricName(result.metric);
    result.moduleCode = paper.getModuleCode();

    for (int index = 0; index < paper.getQuestionCount(); ++index) {
        const double maximum = paper.getQuestionMaximumMarks(index);
        if (maximum <= 0.0 || !paper.hasQuestionMark(index)) {
            return result;
        }

        const double percentage = paper.getQuestionMark(index) / maximum * 100.0;
        if (!result.valid || percentage > result.value) {
            result.value = percentage;
            result.question = paper.getQuestion(index);
            result.valid = true;
        }
    }

    return result;
}
