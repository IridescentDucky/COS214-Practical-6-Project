#include "ExamMarkingFacade.h"
#include "ExamPaper.h"
#include "ExamStatsStrategy.h"

#include <iostream>

ExamMarkingFacade::ExamMarkingFacade(int year)
    : year(year),
      tutor("T1", "Tutor"),
      assistantLecturer("AL1", "Assistant Lecturer"),
      lecturer("L1", "Lecturer"),
      statistics(year, 0.0, 0.0, 0.0, 0.0)
{
    tutor.setNext(&assistantLecturer);
    assistantLecturer.setNext(&lecturer);
}

ExamMarkingFacade::~ExamMarkingFacade()
{
    for (int i = 0; i < papers.getSize(); ++i)
    {
        delete papers.getPaperAt(i);
    }
}

ExamPaper* ExamMarkingFacade::find(int paperIndex) const
{
    ExamPaper* paper = dynamic_cast<ExamPaper*>(papers.getPaperAt(paperIndex));
    if (paper == nullptr)
    {
        std::cout << "[ExamMarkingFacade] No exam paper at index " << paperIndex << std::endl;
    }
    return paper;
}

int ExamMarkingFacade::createExamPaper(const std::string& moduleCode, int duration)
{
    papers.addPaper(creator.createExamPaper(moduleCode, duration, 0.0, year));
    std::cout << "[ExamMarkingFacade] Created " << moduleCode << " paper for " << year << std::endl;
    return papers.getSize() - 1;
}

bool ExamMarkingFacade::addQuestion(int paperIndex, const std::string& question, double maximumMarks)
{
    ExamPaper* paper = find(paperIndex);
    if (paper == nullptr)
    {
        return false;
    }
    paper->addQuestion(question, maximumMarks);
    return true;
}

bool ExamMarkingFacade::captureMarks(int paperIndex)
{
    ExamPaper* paper = find(paperIndex);
    if (paper == nullptr)
    {
        return false;
    }
    paper->setMarker(&tutor);
    paper->mark();
    std::cout << "[ExamMarkingFacade] " << paper->getModuleCode() << " final mark: " << paper->getMarks() << "/" << paper->getMaximumMarks() << std::endl;
    return true;
}

double ExamMarkingFacade::generateStatistics(ExamStatsStrategy* strategy)
{
    if (strategy == nullptr)
    {
        std::cout << "[ExamMarkingFacade] Choose a statistics strategy first." << std::endl;
        return 0.0;
    }
    history.saveMemento(statistics.createMemento());
    statistics.setStrategy(strategy);
    return statistics.calculate(&papers);
}

void ExamMarkingFacade::undoStatistics()
{
    statistics.restoreMemento(history.getMemento());
}
