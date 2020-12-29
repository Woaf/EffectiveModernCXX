#ifndef PERSON_H
#define PERSON_H

using ushort = unsigned short;

class Person {
public: 
	constexpr Person () noexcept;
	constexpr Person (ushort age) noexcept;

private: 
	ushort age;
};


#endif