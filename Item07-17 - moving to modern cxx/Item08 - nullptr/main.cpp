#include <iostream>

void g (void*) { std::cout << "g (void* = 0)" << std::endl; }

void f (int) { std::cout << "f (int)" << std::endl; }
void f (bool) { std::cout << "f (bool)" << std::endl; }
void f (void*) { std::cout << "f (void*)" << std::endl; }
// "just dont overload any function that has a pointer parameter" is just a ridiculous restriction

int iDefinitelyReturnAPointer (bool b) { 
    std::cout << "fake func" << std::endl; 
    return NULL; // warning: implicit conversion of NULL constant to 'int'
                 // we can explicitly cast NULL to an integer with (int)NULL to remove the warning
                 // avoid to return NULL, if the function has no return value use void as return type
                 // if you want to make sure to return a pointer use nullptr instead of NULL
}

int* iDefinitelyReturnAPointer_r (bool b) { 
    std::cout << "valid func" << std::endl; 
    return b ? new int(3) : nullptr; 
}

int main () 
{
    g (0);          // ok, 0 is a fallback value for a pointer
    g (NULL);       // ok, NULL is defined as 0 or 0L, which is a fallback value for a pointer
    g (nullptr);    // ok, nullptr is not an integral type

    // nullptr is not a pointer either, but more like a pointer of all types
    // circular definition: typeof (nullptr) = std::nullptr_t, typeof (std::nullptr_t) = nullptr
    // nullptr cannot be viewed as an integral, therefore it avoids the calling with 0 or NULL ambiguity

    f (0);          // calls f(int), never calls f(void*)
    // f (NULL);    // error! ambiguous function call, NULL can be any of f's parameters
    f (nullptr);    // ok, will call f (void*) only, as nullptr cannot be interpreted as an integral

    auto x = iDefinitelyReturnAPointer (false);
    if (x == 0) {
        // non-ambiguous comparison of x. x will be int, because of the implicit cast
        // to print out the type of x use the following expression std::cout << typeid(x).name();
    }

    auto y = iDefinitelyReturnAPointer_r (true);
    if (y == nullptr) {
        // non-ambiguous comparison of pointer type values
    }

    // templates can filter out bad pointer types! 
    // if 0 or NULL is passed, the type deduction sees these are non-pointer type parameters, and gives a compile error
    // this is not the case when using nullptr

    return 0;
}
