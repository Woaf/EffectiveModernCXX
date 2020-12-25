#ifndef CLASSES_H
#define CLASSES_H

#include <string>
#include <iostream>
#include <memory>
#include <vector>

class Document 
{
public: 
    static Document* createDocument (const std::string& filename);
    static Document* createDocumentWithYear (const std::string& path, unsigned int year);

    std::string GetName () const noexcept;
    unsigned int GetYear () const noexcept;

    virtual ~Document ();

private: 
    Document (const std::string& path, unsigned int year);
    
    std::string name;
    unsigned int year;
};


std::ostream& operator<< (std::ostream& out, const Document& document);


class BadObject 
{
public:
    BadObject () = default;
    BadObject (const std::string& name, size_t id);
    void process (std::vector<std::shared_ptr<BadObject>>& vector);
private:
    std::string name;
    size_t id;
};


class GoodObject : public std::enable_shared_from_this<GoodObject> 
{
public:
    static std::shared_ptr<GoodObject> create (); // factory method

    void process (std::vector<std::shared_ptr<GoodObject>>& vector);

private:
    // private constructors prevent others to create raw pointers.
    // ensures that process gets a valid shared pointer
    GoodObject ();
    GoodObject (const GoodObject& o) = default;
    GoodObject& operator= (const GoodObject& o) = default;
    GoodObject (GoodObject&& o) = default;

    std::string name;
    size_t id;
};


inline std::shared_ptr<GoodObject> GoodObject::create (/*perfect forward params if needed*/)
{
    return std::shared_ptr<GoodObject> (new GoodObject ());
}


#endif // CLASSES_H