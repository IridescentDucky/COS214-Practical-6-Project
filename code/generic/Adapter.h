#ifndef ADAPTER_H
#define ADAPTER_H

#include "Target.h"
#include "Adaptee.h"

#include <iostream>

using namespace std;

/** @brief Adapts an Adaptee to the Target interface. */
class Adapter : public Target {
public:	
	/** @brief Creates an adapter for an external system.
	 *  @param adaptee System whose interface is adapted.
	 */
    Adapter(Adaptee* adaptee);
	/** @brief Translates the Target request into the adaptee's request. */
	void request();

private:
    Adaptee* adaptee;
};

#endif