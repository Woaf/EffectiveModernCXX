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

int f () throw () {return 4;}  // c++98 way of saying "i don't throw any exceptions"
int f () noexcept {return 5;}  // c++11 --||--

// if an exception escapes functions 'f', then the specification 
// is violated.
// c++98: if an exception is thrown: unwinds the call stack before termination
// c++11: POSSIBLY unwinds the call stack before termination

// noexcept optimalization: 
// when declaring the exception specification of a function to be noexcept
// the compiler can make optimalizations on the generated code. 'noexcept'
// ensures the following:  "In a noexcept function, optimizers do not need to keep 
// the runtime stack in an unwindable state if an exception would propagate out of 
// the function, nor must they ensure that objects in a noexcept function are 
// destroyed in the inverse order of construction should an exception 
// leave the function.

// this optimalization is not possible in c++98 throw (), and in any other
// functions that are not declared 'noexcept'

int main () 
{
    // ???

    return 0;
}