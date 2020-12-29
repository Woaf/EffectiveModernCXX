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

Class::~Class () = default;

