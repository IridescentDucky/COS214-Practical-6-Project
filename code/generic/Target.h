#ifndef TARGET_H
#define TARGET_H

#include <iostream>

using namespace std;

/** @brief Interface expected by clients of an external system adapter. */
class Target {
public:	
	/** @brief Destroys the target through its base interface. */
	virtual ~Target() {}
	/** @brief Performs a request using the target interface. */
	virtual void request() = 0;
};

#endif