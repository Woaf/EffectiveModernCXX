#include "classes.hpp"
#include <memory>

auto docDeleter = [] (Document* doc) {
	std::cout << "Running custom deleter on std::shared_ptr<Document>" << std::endl;
	delete doc;
};


auto BODeleter = [] (BadObject* bo) {
	std::cout << "Running custom deleter on std::shared_ptr<BadObject>" << std::endl;
	delete bo;
};


int main ()
{
	/*
	// DO NOT DO THIS:
	{
		Document* pDoc = Document::createDocument ("nice.pdf");
		std::shared_ptr<Document> sharedP1 (pDoc, docDeleter);
		std::shared_ptr<Document> sharedP2 (pDoc, docDeleter);
	} // undefined behavior when the second custom deleter runs
	  // in my case, the deleter threw an exception (MSVC v142)
	*/

	// this would be a bit better
	{
		std::shared_ptr<Document> sharedP1 (Document::createDocument ("nice.pdf"), docDeleter);
		std::shared_ptr<Document> sharedP2 (sharedP1);
	}

	/* DO NOT DO THIS EITHER:
	{
		std::vector<std::shared_ptr<BadObject>> vector;
		std::shared_ptr<BadObject> badPointer (new BadObject ("asdf", 0), BODeleter);
		badPointer->process (vector);
	}
	*/

	{
		std::vector<std::shared_ptr<GoodObject>> vector;
		std::shared_ptr<GoodObject> goodPointer (GoodObject::create ());
		goodPointer->process (vector);
	}

	{
		std::unique_ptr<Document, decltype (docDeleter)> pDocument = Document::createUPtr ("File.pdf");
		std::cout << *pDocument << std::endl;
		/*
			When converting a uniquePtr to a sharedPtr as such, std::move *must* be used!
		*/
		std::shared_ptr<Document> shpDocument = std::move (pDocument);
		if (pDocument != nullptr) {
			std::cout << *pDocument << std::endl;
		}

		std::cout << *shpDocument << std::endl;
	}


	return 0;
}