#include "ExamDelivery.h"

#include "Marker.h"

ExamDelivery::ExamDelivery(AbstractExamPaper* paper)
    : ExamDeliveryService(paper) {
}

void ExamDelivery::attach(Marker* marker) {
    if (marker != nullptr) {
        markerObservers.push_back(marker);
    }
}

void ExamDelivery::detach(Marker* marker) {
    for (auto it = markerObservers.begin(); it != markerObservers.end(); ++it) {
        if (*it == marker) {
            markerObservers.erase(it);
            return;
        }
    }
}

void ExamDelivery::notify() {
    for (Marker* marker : markerObservers) {
        if (marker != nullptr) {
            marker->update();
        }
    }
}

AbstractExamPaper* ExamDelivery::getExamPaper() {
    return examPaper;
}
