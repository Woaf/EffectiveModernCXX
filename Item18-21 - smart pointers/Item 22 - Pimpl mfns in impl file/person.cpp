#include "person.hpp"

constexpr Person::Person () noexcept : 
	age (0)
{
}

constexpr Person::Person (ushort age) noexcept : 
	age (age)
{
}
