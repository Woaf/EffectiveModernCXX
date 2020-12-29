#ifndef CLASSES_H
#define CLASSES_H

#include <string>
#include <vector>
#include "person.hpp"


class Class {
public:
	Class ();

private:
	std::string name;
	std::vector<double> data;
	Person p1, p2, p3;
};


#endif
