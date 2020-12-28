#include "classes.hpp"
#include <unordered_map>
#include <algorithm>

namespace Woaf
{
	using DocID = unsigned short;
	using library = std::unordered_map<DocID, std::weak_ptr<const Document>>;
}

static void TestWeakPointers () 
{
	std::shared_ptr<Person> p_person = Person::createSharedPtr (26, "Balint");
	std::weak_ptr<Person> wp_person (p_person);

	if (!wp_person.expired ()) {
		std::cout << *p_person << std::endl;
	}

	p_person = nullptr;

	// A way to generate a shared ptr from a weak pointer (thread safe)
	std::shared_ptr<Person> sharedCopy = wp_person.lock ();
	if (sharedCopy == nullptr) {
		std::cout << "The weak pointer was already expired..." << std::endl;
	}

	// Another way of creating a readable shared pointer from a weak pointer (also thread safe)
	// throws an exception
	try {
		std::shared_ptr<Person> sharedPtr = std::shared_ptr<Person> (wp_person);
	} catch (const std::bad_weak_ptr& ex) {
		std::cout << ex.what () << std::endl;
	}
}

int main ()
{
	// basics 
	TestWeakPointers ();

	// book example
	{
		std::shared_ptr<Document> d1 = Document::CreateDocument ("title1");
		std::shared_ptr<Document> d2 = Document::CreateDocument ("title2");
		std::shared_ptr<Document> d3 = Document::CreateDocument ("title3");
		std::shared_ptr<Document> d4 = Document::CreateDocument ("title4");
		std::shared_ptr<Document> d5 = Document::CreateDocument ("title5");
		std::shared_ptr<Document> d6 = Document::CreateDocument ("title6");
		std::shared_ptr<Document> d7 = Document::CreateDocument ("title7");

		Woaf::library cache {{1, d1}, 
							 {2, d2},
							 {3, d3},
							 {4, d4},
							 {5, d5},
							 {6, d6},
							 {7, d7}};


		d2 = nullptr;
		d7 = nullptr;

		std::for_each (cache.begin (), cache.end (), 
					   [] (std::pair<Woaf::DocID, std::weak_ptr<const Document>> e) {
						   if (!e.second.expired ()) {
							   // I used .lock () to avoid the bad_weak_ptr exception
							   std::cout << *(e.second.lock ()) << std::endl;
							}
					   });
	}


	return 0;
}