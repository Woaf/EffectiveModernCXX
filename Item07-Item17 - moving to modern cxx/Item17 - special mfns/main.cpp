#include <utility>
#include <iostream>

// I. everything is defaulted
class I {
};

// II. Any user defined constructor (paramtericized constructor)
// other special mfunctions are gnerated by the compiler
class II {
public: 
    II (int i) {}
};


// III. user defined default ctor
// just like in the case of user defined parametricized ctor
// the compiler generates the other special member functions
class III {
public: 
    III () {}
};

// IV. user declared dtor
// c++11: move ctor and = operator are not declared!!!
// other special member functions are defaulted
class IV {
public: 
    ~IV () {}
    // reasons for defaulting the copy methods:
        // if a destructor is declared, then it indicates that
        // simple memberwise copy is inappropriate -> copy methods
        // should not be generated. 
        // This view was not appreciated, so c++98 generated copy methods,
        // and in c++11 this is also the case, because it would break too much
        // legacy code otherwise. :(
    // reasons for not declaring the move methods: 
        // same as in the case of copy methods, but since they were
        // introduced in c++11, they are not declared! (hence, would not break 
        // existing code)
};


// V. user declared copy ctor
// default ctor, and move methods are not generated
// copy = operator and destructor are defaulted
class V 
{
public: 
    V (const V& other) {}
    // copy assignment operator and copy ctor do not disturb each other
    // reasons for why move ctor and move assignment operator are not generated:
        // same as previously
};

// VI. only copy assignment decalred
// ctor, copy ctor, and dtor are generated
// move methods not generated
class VI
{
public: 
    VI& operator= (const V& other) {}
};


// VII. only move ctor declared
// default ctor and move = NOT DECLARED
// copy methods DELETED
// destructor defaulted
class VII 
{
public: 
    VII (VII&& other) {}
};

// VIII. 
// only move assignment declared
class VIII 
{
public: 
    VIII& operator= (VIII&& other) { std::cout << "move = called" << std::endl; }
};

int main () 
{
    // I.
    {
        I i;        // default ctor
        I i2 (i);   // copy ctor
        I i3;
        i3 = i2;    // copy assignment operator
        I i4 (std::move (I ())); // move ctor
        I i5;
        // i5 = std::move(i4);    // move assignment operator
    } // I dtor

    // II.
    {
        // II i;        // error, no default ctor
        II i2 {7};      // pd ctor
        II i3 {i2};     // copy ctor
        II i4 = i3;     // copy assigment operator
        II i5 (std::move (II (7)));   // move ctor
        II i6 (7);  
        // i6 = std::move ((i5)); // move assignment operator
    } // II dtor

    // III. 
    { 
    // same as I.
    }

    // IV.
    {
        IV i;           // default ctor
        IV i2 (i);      // copy ctor
        i2 = i;         // copy assigment operator
        IV i3 (std::move (i2));  // move cotr not generated -> copy ctor!
        // IV i4 = std::move (i3); // error, no move ctor!!
    } // IV. dtor

    // V.
    {
        // is it even possible to create V??
    }

    // VI.
    {
        VI i; // default ctor
        VI i2 (i); // copy ctor
        i2 = i; // copy assigment operator
        VI i3 (std::move(VI ())); // request for move, but no move generated -> copy ctor
        i3 = std::move (i2); // request for move, but no move generated -> copy = operator
    } // VI dtor

    // VII. same as V? 
    {
    }

    // VIII. 
    {
        VIII i; // default ctor defaulted
        VIII ii;
        ii = std::move (VIII ()); // ???

    } // VIII dtor

    return 0;
}