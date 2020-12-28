#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>

class PDF 
{
public: 
	static PDF createNamedPDF (const std::string& name);
	static PDF createNamedPDFWithOwner (const std::string& name, const std::string& owner);

	std::string GetName () const noexcept;
	std::string GetOwner () const noexcept;

private: 
	PDF (const std::string& name, const std::string& owner);

	std::string name;
	std::string owner;
};


std::ostream& operator<< (std::ostream& out, const PDF& pdf);


#endif 
