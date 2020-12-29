#ifndef CLASSES_H
#define CLASSES_H

#include <string>
#include <vector>
#include <memory>

class Class {
public:
	Class ();
	Class (const Class& other);
	Class (Class&& other);
	Class& operator= (const Class& other);
	Class& operator= (Class&& other);

	~Class ();

private:
	struct ClassImpl;
	std::unique_ptr<ClassImpl> impl;
};


#endif
