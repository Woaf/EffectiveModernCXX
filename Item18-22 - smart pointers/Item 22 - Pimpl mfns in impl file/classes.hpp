#ifndef CLASSES_H
#define CLASSES_H

#include <string>
#include <vector>
#include <memory>

class Class {
public:
	Class ();
	~Class ();

private:
	struct ClassImpl;
	std::unique_ptr<ClassImpl> impl;
};


#endif
