#include <iostream>
#include <vector>
#include <tuple>
#include <list>

typedef std::vector<std::pair<int, int>> IntVector_td;
using IntVector_u = std::vector<std::pair<int, int>>;

// while typedefs cannot, aliasing can handle templates
template <typename T>
class MyAlloc {};

template <typename T>
using MyAllocList = std::list<T, MyAlloc<T>>; // its that easy!
// client would use this as: 
// MyAllocList<int> myList;

// the following workaround shows how templates can be used with typedefs
template <typename T>
struct TemplateStruct
{
    typedef std::list<T, MyAlloc<T>> type;
};
// which the client would use as: 
// TemplateStruct<int>::type ls;

template <typename T>
struct MyNewVector
{
    typedef std::vector<T> MyNewTypedef;
};


// +++ dependent types 
template <typename T>
struct ASDF 
{
    typedef int type;
};

template <typename T>
struct MyNewType
{
    typename ASDF<T>::type a; // writing "typename" is necessary, due to dependent type 
                              // the compiler would not be able to distingish ::type  
                              // between a type or a member
};
// --- dependent types

// +++ non-dependent types
template <typename T>
using NewVectorName = std::vector<T>;

template <typename T>
struct AnotherStruct
{
    NewVectorName<T> vec; // "typename" is not needed, because "NewVectorName" clearly identifies 
                          // a type
};
//

int main ()
{
    IntVector_u intPairs { {3, 4}, {5,8}, {11, 75} };

    for (const auto& i : intPairs) {
        std::cout << i.first << ", " << i.second << std::endl;
    }

    return 0;
}
