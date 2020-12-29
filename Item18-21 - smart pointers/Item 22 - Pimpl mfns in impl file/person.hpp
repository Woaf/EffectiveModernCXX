#ifndef PERSON_H
#define PERSON_H

using ushort = unsigned short;

class Person {
public: 
	Person () noexcept;
	Person (ushort age) noexcept;

private: 
	ushort age;
};


#endif