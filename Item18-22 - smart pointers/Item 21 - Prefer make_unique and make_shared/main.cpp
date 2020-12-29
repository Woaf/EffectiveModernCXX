#include "classes.hpp"

int main ()
{
	{
		std::unique_ptr<PDF> uptr1 (new PDF (PDF::createNamedPDF ("book1.pdf")));
		// vs.
		auto uptr2 (std::make_unique<PDF> (PDF::createNamedPDF ("book2.pdf")));
		std::cout << *uptr1 << std::endl;
		std::cout << *uptr2 << std::endl;
	}

	{

	}

	return 0;
}