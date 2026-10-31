#include "AbstractExamPaper.h"

#include "Marker.h"
#include "States.h"

#include <algorithm>

AbstractExamPaper::AbstractExamPaper(
    std::string code,
    int duration,
    double initialMarks,
    int year)
    : state(new WrittenState(this)),
      moduleCode(code),
      examDuration(duration),
      marks(initialMarks),
      year(year) {
}

AbstractExamPaper::~AbstractExamPaper() {
    delete state;
    state = nullptr;

    for (Marker* observer : observers) {
        if (observer != nullptr) {
            observer->setExamPaper(nullptr);
        }
    }
}

double AbstractExamPaper::getMarks() const {
    return marks;
}

double AbstractExamPaper::getBonusMarks() {
    return 0.0;
}

int AbstractExamPaper::getExtraTime() {
    return 0;
}

void AbstractExamPaper::attach(Marker* observer) {
    if (observer == nullptr ||
        std::find(observers.begin(), observers.end(), observer) != observers.end()) {
        return;
    }

    observers.push_back(observer);
    observer->setExamPaper(this);
}

void AbstractExamPaper::detach(Marker* observer) {
    std::vector<Marker*>::iterator found =
        std::find(observers.begin(), observers.end(), observer);
    if (found == observers.end()) {
        return;
    }

    (*found)->setExamPaper(nullptr);
    observers.erase(found);
}

void AbstractExamPaper::notify() {
    for (Marker* observer : observers) {
        if (observer != nullptr) {
            observer->update();
        }
    }
}
