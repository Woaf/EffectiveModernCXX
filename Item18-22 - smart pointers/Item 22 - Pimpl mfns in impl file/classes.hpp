#ifndef CLASSES_H
#define CLASSES_H

#include <string>
#include <vector>


class Class {
public:
	Class ();
	~Class ();

private:
	struct ClassImpl;
	ClassImpl* impl;
};


#endif
