#include "Adapter.h"

Adapter::Adapter(Adaptee* adaptee) : adaptee(adaptee) {
}

void Adapter::request() {
    cout << "(Adapter) Sending request" << endl;

    adaptee->specifiedRequest();
}