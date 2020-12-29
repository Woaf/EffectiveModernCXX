#include "classes.hpp"

Document::Document (const std::string& name) :
	name (std::make_unique<std::string> (name))
{
}

std::string Document::GetName () const noexcept
{
	if (name != nullptr) {
		return *name;
	}
	return std::string ();
}

std::ostream& operator<<(std::ostream& out, const Document& doc)
{
	out << "Printing: {" << doc.GetName () << "}";
	return out;
}
