#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>

class Investment {
public:
    Investment (int id, const std::string& name) : id (id), name (name) {}
    virtual ~Investment () {}

    virtual void printName () const noexcept { std::cout << name << std::endl; }
protected:
    int id;
    std::string name;
};

class Stock : public Investment 
{
public:
    Stock (int id, const std::string& name) : Investment (id, name) {}
};

class Bond : public Investment 
{
public:
    Bond (int id, const std::string& name) : Investment (id, name) {}
};

class RealEstate : public Investment
{
public: 
    RealEstate (int id, const std::string& name) : Investment (id, name) {}
};


// DOCUMENT
class Document
{
public: 
    Document (const std::string& name);

    std::string GetName () const noexcept;
private:
    std::unique_ptr<std::string> name;
};

std::ostream& operator<< (std::ostream& out, const Document& doc);


#endif