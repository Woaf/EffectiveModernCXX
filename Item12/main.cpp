#include <iostream>
#include <memory>

class Base
{
public:
    void f () { std::cout << "Base::f" << std::endl; }
    virtual void g () { std::cout << "Base::g" << std::endl; }
    virtual void h () { std::cout << "Base::h" << std::endl; }

    virtual void i () { std::cout << "Base::i" << std::endl; }

    virtual ~Base () {}
};

class Derived : public Base
{
public:
    void f () { std::cout << "Derived::f" << std::endl; }
    void g (int) { std::cout << "Derived::g" << std::endl; }
    void h () override { std::cout << "Derived::h" << std::endl; }

    void i () override final { std::cout << "Derived::i" << std::endl; }

    virtual ~Derived () {}
};

// final class, it cannot be inherited
class DeepDerived final : public Derived
{
public:
    // void i () override { std::cout << "DeepDerived::i" << std::endl; } // error, cannot override a final fn
};

// Error, final declared calsses cannot be inherited
// class ErrorDerived : public DeepDerived {
//
// };


/*
 * Points considered when overloading:
 * 1) the function is declared as virtual in the base class
 * 2) the name of the function is the same in both base and derived classes
 * 3) The functions have the same parameter list
 * 4) const-ness is the same for the functions
 * 5) Return type and expcetion handling needs to be the same
 * 6) Reference qualifiers must be the same
 */

int main()
{
    Base b;
    Derived d;

    b.f ();
    d.f ();

    Base* objectPtr = new Derived ();
    objectPtr->f(); // calls Base::f, because it is not virtual
    objectPtr->g (); // calls Base::g, because parameter type matches Base::g better
    objectPtr->h ();
    objectPtr->i ();

    delete objectPtr;

    return 0;
}
