#include "classes.hpp"

ushort Person::GetAge () const noexcept
{
	return age;
}

std::string Person::GetName () const noexcept
{
	return name;
}

Person::Person (ushort age, const std::string& name) noexcept :
	age (age), 
	name (name)
{
}

std::ostream& operator<<(std::ostream& out, const Person& p) {
	out <<
		"Person: {name: " <<
		p.GetName () <<
		", age: " <<
		p.GetAge () <<
		"}; ";
	return out;
}

std::ostream& operator<<(std::ostream& out, const Document& doc)
{
	out <<
		"Doc: " <<
		doc.GetName ();
	return out;
}

std::shared_ptr<Document> Document::CreateDocument (const std::string& name)
{
	return std::shared_ptr<Document> (new Document (name));
}

std::string Document::GetName () const noexcept
{
	return name;
}

Document::Document (const std::string& name) : 
	name (name)
{
}
