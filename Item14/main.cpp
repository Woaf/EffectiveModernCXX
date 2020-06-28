// In c++98 exception specification is cumbersome, 
// as one have to specify all possible exceptions that 
// a function is able to throw.

// In c++11 and up, its established that what really matters
// is whether a function throws and exception or not.

// new keyword: 'noexcept', means that functions with this 
// specifier are guaranteed not to throw any exceptions

// Clients can query the exception-emmitting behavior of 
// a function (by checking for 'noexcept'). This can affect 
// the efficiency or the expcetion safety of the caller.

// ! 'noexcept' is just as imporant as 'const'! Not specifing 
// it when it really should be is bad interface design!

// It also compilers to generate better object code.

int f () throw ();  // c++98 way of saying "i don't throw any exceptions"
int f () noexcept;  // c++11 --||--

// if an exception escapes functions 'f', then the specification 
// is violated.
// c++98: if an exception is thrown: unwinds the call stack before termination
// c++11: POSSIBLY unwinds the call stack before termination
// apparently, this is a huge difference for code generation


int main () 
{
    // ???

    return 0;
}