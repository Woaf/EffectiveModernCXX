#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>

using ushort = unsigned short;

class Person {
public:
	template<typename... Ts>
	static Person create (Ts... params) noexcept;

	template<typename... Ts>
	static std::shared_ptr<Person> createSharedPtr (Ts... params);

	ushort GetAge () const noexcept;
	std::string GetName () const noexcept;

private: 
	Person (ushort age, const std::string& name) noexcept;

	ushort age;
	std::string name;
};


template<typename ...Ts>
inline Person Person::create (Ts... params) noexcept
{
	return Person (std::forward<Ts> (params)...);
}


auto personDeleter = [] (Person* person) {
	std::cout << "Running custom deleter for the person object..." << std::endl;
	delete person;
};


template<typename ...Ts>
inline std::shared_ptr<Person> Person::createSharedPtr (Ts... params)
{
	return std::shared_ptr<Person> (new Person (std::forward<Ts> (params)...), personDeleter);
}


std::ostream& operator<< (std::ostream& out, const Person& p);


class Document {
public: 
	static std::shared_ptr<Document> CreateDocument (const std::string& name);

	std::string GetName () const noexcept;
private:
	Document (const std::string& name);
	std::string name;
};


std::ostream& operator<< (std::ostream& out, const Document& doc);


#endif

