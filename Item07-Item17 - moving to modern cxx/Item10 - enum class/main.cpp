#include <iostream>
#include <string>
#include <tuple>
#include <vector>

// getting the underlying type of an enum 
// (for the use case)
// constexpr - forditasi idoben kieretkelheto fv???
// noexcept - ??? jelzes a forditonak, hogy biztos nem dobodik kivetel
template <typename E>
constexpr std::underlying_type_t<E> toUnderlyingType (E enumerator) noexcept
{
	return static_cast<std::underlying_type_t<E>> (enumerator);
}


int main ()
{
	// unscoped enums pollute the namespace
	enum Colors1
	{
		red, 
		green, 
		blue
	};

	// int red = 2; // does not compile as Colors1::red is within the same scope

	int x = red; // Implicit conversion of "unscoped enums" to integral type. same as "int x = Color1::red"

	enum class Colors2
	{
		red, 
		green, 
		blue
	};

	// int x = Colors2::red; // does not compile, as no implicit conversion happens with "scoped enums"
	Colors2 colorValue = Colors2::green; // colorValue = green would not work, as it'd refer to 
										 // Colors1::green, but then there would be a type mismatch
										 // (and hence, would not compile)

	// enum UnscopedEnum; // compile error! unscoped enums cannot be forward declared, as their so called
					      // "underlying type" cannot be determined 
					      // underlying type depends on the most compact possible type for the enums (char, int, long, etc), 
					      // hence all the values need to be defined. 

	enum class ScopedEnum; // scoped enums / enum classes can be forward declared as their underlying type always defaults to "int"
						   // (the size of each element is known)

	enum class ScopedEnum
	{
		VALUE1, 
		VALUE2, 
		VALUE3
	};

	// specifying underlying types
	// can be done for both "enums" and "enum classes"
	enum SpecifiedUnscopedEnum : int;		 // forward decalring enum with underlying type of int
	enum class SpecifiedScopedEnum : size_t; // forward declaring enum class with underlying type of size_t

	// red is 0
	if (red < 4.21) {
		std::cout << "Color1::red < 4.21" << std::endl;
	}

	// if (Colors2::red < 24.1) {} // does not compile - no implicit conversion of enum class to integral type
	// workaround: (Colors2::red == 0)
	if (static_cast<int>(Colors2::red) < 24.1) {
		std::cout << "static_cast<int>(Colors2::red) < 24.1" << std::endl;
	}

	// usecase: indexing
	enum UserInfo_e { ID, NAME, EMAIL };
	enum class UserInfo_c { ID, NAME, EMAIL };

	std::vector<std::tuple<int, std::string, std::string>> users { {1, "Balint", "a@a.a"}, {2, "asdf", "asdf@asd.hu"} };
	std::cout << std::get<NAME> (users.at (0)) << std::endl; // Balint
	//vs.
	std::cout << std::get<static_cast<size_t>(UserInfo_c::NAME)> (users.at (0)) << std::endl; // Balint
	// with the std::underlying_type getter function
	// this is preferred as the scoped enums do not pollute 
	std::cout << std::get<toUnderlyingType (UserInfo_c::EMAIL)> (users.at (1)) << std::endl;

	return 0;
}