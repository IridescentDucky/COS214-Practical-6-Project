#include "Adapter.h"

void Adapter::request() {
    cout << "(Adapter) Sending request" << endl;

    adaptee->specifiedRequest();
}