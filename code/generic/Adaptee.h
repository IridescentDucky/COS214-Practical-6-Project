#ifndef ADAPTEE_H
#define ADAPTEE_H

#include <iostream>
#include <string>

using namespace std;

class Adaptee {
public:	
	Adaptee(const string& name = "External system");
	void specifiedRequest();
	void setName(const string& name);
	string getName() const;

private:
	string name;
};

#endif
