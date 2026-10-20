#ifndef TARGET_H
#define TARGET_H

#include <iostream>

using namespace std;

class Target {
public:	
	virtual void request() = 0;
};

#endif