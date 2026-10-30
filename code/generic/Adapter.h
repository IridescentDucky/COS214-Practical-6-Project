#ifndef ADAPTER_H
#define ADAPTER_H

#include "Target.h"
#include "Adaptee.h"

#include <iostream>

using namespace std;

class Adapter : public Target {
public:	
    Adapter(Adaptee* adaptee);
	void request();

private:
    Adaptee* adaptee;
};

#endif