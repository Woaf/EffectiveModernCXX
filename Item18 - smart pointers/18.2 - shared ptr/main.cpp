#include "classes.hpp"
#include <memory>

auto docDeleter = [] (Document* doc) {
	std::cout << "Running custom deleter on std::shared_ptr<Document>" << std::endl;
	delete doc;
};


auto BODeleter = [] (BadObject* bo) {
	std::cout << "Deleting bad object..." << std::endl;
	delete bo;
};


auto GODeleter = [] (GoodObject* go) {
	std::cout << "Deleting good object..." << std::endl;
	delete go;
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
	  // in my case, the deleter threw an exception
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


	return 0;
}