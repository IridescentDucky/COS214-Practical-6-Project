#include "Adaptee.h"

Adaptee::Adaptee(const string& name) : name(name) {
}

void Adaptee::specifiedRequest() {
    cout << "(Adaptee) " << name << " recorded the update" << endl;
}

void Adaptee::setName(const string& name) {
    if (!name.empty()) {
        this->name = name;
    }
}

string Adaptee::getName() const {
    return name;
}
