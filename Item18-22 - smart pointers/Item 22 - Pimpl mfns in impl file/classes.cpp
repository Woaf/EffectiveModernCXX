#include "classes.hpp"

#include "person.hpp"
#include <string>
#include <vector>

struct Class::ClassImpl {
	std::string name;
	std::vector<double> data;
	Person p1, p2, p3;
};

Class::Class () : 
	impl (std::make_unique<ClassImpl> ())
{
}

Class::Class (const Class& other) : 
	impl (std::make_unique<ClassImpl> (*other.impl))
{
}

Class::~Class () = default;

Class::Class (Class&& other) = default;

Class& Class::operator=(const Class & other)
{
	*impl = *other.impl;
	return *this;
}

Class& Class::operator=(Class&& other) = default;

