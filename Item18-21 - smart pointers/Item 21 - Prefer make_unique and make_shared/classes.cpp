#include "classes.hpp"

PDF PDF::createNamedPDF (const std::string& name)
{
	return PDF (name, std::string ());
}

PDF PDF::createNamedPDFWithOwner (const std::string& name, const std::string& owner)
{
	return PDF (name, owner);
}

std::string PDF::GetName () const noexcept
{
	return name;
}

std::string PDF::GetOwner () const noexcept
{
	return owner;
}

PDF::PDF (const std::string& name, const std::string& owner) : 
	name (name), 
	owner (owner)
{
}

std::ostream& operator<<(std::ostream& out, const PDF& pdf)
{
	out <<
		"PDF {name: " <<
		pdf.GetName () <<
		", owner: " <<
		pdf.GetOwner () <<
		"}";
	return out;
}
