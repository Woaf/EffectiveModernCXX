#include "classes.hpp"

Document* Document::createDocument (const std::string& filename)
{
	return new Document (filename, 0);
}

Document* Document::createDocumentWithYear (const std::string& path, unsigned int year)
{
	return new Document (path, year);
}

std::unique_ptr<Document, decltype (docDeleter)> Document::createUPtr (const std::string& name) 
{
	return std::unique_ptr<Document, decltype (docDeleter)> (new Document (name, 0), docDeleter);
}

std::string Document::GetName () const noexcept
{
	return name;
}

unsigned int Document::GetYear () const noexcept
{
	return year;
}

Document::~Document ()
{
	std::cout << "Running destructor of Document..." << std::endl;
	name = std::string ();
	year = 0;
}

Document::Document (const std::string& name, unsigned int year) :
	name (name), 
	year (year)
{
}

std::ostream& operator<< (std::ostream& out, const Document& document)
{
	out <<
		"Document: {Name: " <<
		document.GetName () <<
		", " <<
		document.GetYear () <<
		"}";
	return out;
}

BadObject::BadObject (const std::string& name, size_t id) :
	name (name),
	id (id)
{
}


void BadObject::process (std::vector<std::shared_ptr<BadObject>>& vector) 
{
	vector.emplace_back (this);
}


GoodObject::GoodObject () :
	name (std::string ()),
	id (0)
{
}

std::shared_ptr<GoodObject> GoodObject::create ()
{
	return std::shared_ptr<GoodObject> (new GoodObject (), GODeleter);
}

void GoodObject::process (std::vector<std::shared_ptr<GoodObject>>& vector)
{
	vector.emplace_back (shared_from_this ());
}

GoodObject::~GoodObject ()
{
	std::cout << "Running destructor of GoodObject..." << std::endl;
	name = std::string ();
	id = 0;
}

