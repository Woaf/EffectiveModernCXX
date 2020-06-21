#include <iostream>

// I. c++98: declaring a function private, without definition
class A
{
public:
    A () = default;
private:
    A (const A& other); // hiding the copy constructor, leaving it undefined
    // C++98 way of 'deleting' methods
};


// II. deleted member functions
class B
{
public:
    B () = default;
    B (const B& other) = delete;
};

// III. deleting non-member functions
int f (int) = delete;

// IV. deleted template non-member functions
// this fn can be called with double, bool, char, int, as well as many other
// parameter types that implicitly convert to int
int g (int) { std::cout << "g (int)" << std::endl; return 1; }

int g_2 (int) { std::cout << "g_2 (int)" << std::endl; return 5; }
int g_2 (bool) = delete;
int g_2 (char) = delete;
int g_2 (double) = delete; // also deletes "g_2 (float)", as float will more likely to chose 'double' over 'int'


// V. deleting template specialized member functions
class C
{
public:
    template<typename T>
    void f (T) { std::cout << "non-specialized template fn C::f" << std::endl; }

private:
    // hiding a template specialized version of 'f' in private fields would not work
    // as template specialized functions need to have identical visibilities.
    // therefore C++98 would not be able to do such:
    // template <>
    // void f <double> (double) = delete;
};

// template specialized member functions need to be declared outside of class, within the same namespace
template<>
void C::f<char> (char) = delete;


int main()
{
    // I. hidden methods
    A a1; // ok, calls default ctor
    // A a2 = a1; // error! tries to call hidden copy constructor.
    // It is unknown for the client whether it is defined or not.

    // II. deleted methods
    B b1; // ok, calles default ctor
    // B b2 = b1; // error! tries to call copy ctor. gives relevant compile error!

    // III. deleted non-member fns
    // int x = f (84); // error! function f, with return type of int and
    // parameter of int cannot be called as it is declared deleted

    // IV. calling non-member functions with implicitly converting type parameters
    int x1 = g (8); // trivial use of function g (int)
    int x2 = g (true);  // non-tirvial use of g (bool -> int)
    int x3 = g (3.54);  // non-trivial use of g (double -> int)
    int x4 = g (1.65f); // non-trivial use of g (float -> double -> int)
    int x5 = g ('g');   // non-trivial use of g (char -> int)

    int y1 = g_2 (8); // ok, calls g_2 with int parameter
    // int y2 = g_2 (true); // error, tries to call deleted function
    // int y3 = g_2 ('c'); // error, tries to call deleted function
    // int y4 = g_2 (1.54f); // error, tries to call deleted function [g_2 (double)]
    // int y5 = g_2 (42.23); // error, tries to call deleted function

    // V. deleting template spec. memeber functions
    C c;
    c.f (8); // ok, calls f(T -> int) template method
    // c.f ('c'); // error! tries to call deleted template spec'd method
    c.f (C ()); // ok, calls f (T -> C) template method

    return 0;
}
