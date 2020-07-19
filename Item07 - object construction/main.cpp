#include <iostream>
#include <initializer_list>

class A
{
public: 
	A () { std::cout << "empty ctor" << std::endl; }
	A (int x, int y) { std::cout << "param ctor" << std::endl; }
};

class B
{
public:
	B () { std::cout << "empty ctor" << std::endl; }
	B (int x, int y) { std::cout << "param ctor" << std::endl; }

	template <typename T>
	B (std::initializer_list<T> li) { std::cout << "init list ctor" << std::endl; }
};

class C
{
public: 
	C () { std::cout << "empty ctor" << std::endl; }
	C (bool b) { std::cout << "param ctor" << std::endl; }

	operator int () {}

	template <typename T>
	C (std::initializer_list<T> li) { std::cout << "init list ctor" << std::endl; }
};

int main ()
{
	A a;				// empty ctor
	A a2 ();			// warning - function declaration (most vexing parse)
	A a3 (2, 4);		// param ctor
	A a4 {};			// empty ctor
	A a5 = {};			// empty ctor - same as without the '='
	A a6 = {3, 4};			// param ctor

	std::cout << std::endl;

	B b;				// empty ctor
	B b2 ();			// warning - function decl
	B b3 {};			// empty ctor !
	B b4 ({});			// init list ctor -> empty ctor !
	B b5 { 3, 4 };		// init list ctor
	B b6 { 2, 3, 4 };	// init list ctor
	B b7 (3, 4);		// param ctor

	std::cout << std::endl;

	C c { true };		// init list ctor ! 
	C c2 (true);		// param ctor
	
	// int x {5.4}; 	// error! no implicit conversion allowed!

	return 0;
}
