#ifndef ADAPTEE_H
#define ADAPTEE_H

#include <iostream>
#include <string>

using namespace std;

/** @brief External system with an interface incompatible with Target. */
class Adaptee {
public:	
	/** @brief Creates an external system.
	 *  @param name Initial system name.
	 */
	Adaptee(const string& name = "External system");
	/** @brief Performs the external system's specific request. */
	void specifiedRequest();
	/** @brief Changes the external system's name.
	 *  @param name New system name.
	 */
	void setName(const string& name);
	/** @brief Gets the external system's name.
	 *  @return The current system name.
	 */
	string getName() const;

private:
	string name;
};

#endif
