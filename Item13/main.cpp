#include <iostream>
#include <vector>

// I. Prefer const_iterator to iterator
// const_iterator: pointer-to-const

// cxx98: const iterators were not practical to use 
// "use const 'whenever possible' became 'whenever practical'"
// getting a const_iterator in c++98 was a bit difficult
// used casts :/ 


// this works in c++14, but not in c++11, 
// as cbegin () and cend () were left out 
template <typename T, typename V>
void findAndInsert (T& container, const V& targetV, const V& insertV)
{
    auto it = std::find (std::cbegin (container), std::cend (container), targetV);
    container.insert (it, insertV);
}

// II. we can write our own cbegin and cend non-member
// functions for c++11!
template <typename T>
auto cbegin (const T& container) -> decltype (std::begin (container))
{
    // why is this sufficient? 
    // this function gets container as a const ref, meaning that its begin() will be 
    // pointing to a const -> just like a const iterator -> just like const_iterator
    return container.begin();
}

template <typename T>
auto cend (const T& container) -> decltype (std::end (container))
{
    // same reasoning as the previous case
    return std::end (container);
}

int main () 
{
    // I.
    std::vector <int> numbers { 3, 65, 1, 34, 12, 93 };
    // begin () - end (): iterator
    for (auto it = numbers.begin (); it != numbers.end (); ++it) {
        std::cout << *it << std::endl;
    }

    // cbegin () - cend (): const_iterator
    for (auto cit = numbers.cbegin (); cit != numbers.cend (); ++cit) {
        std::cout << *cit << std::endl;
    }

    // the type of the variable in a ranged loop is whatever type
    // the conatiner holds.
    // in this case, 'i' will be of type 'int'
    for (auto i : numbers) {
        std::cout << i << std::endl;
    }


    findAndInsert (numbers, 99, 11);
    for (auto i : numbers) {
        std::cout << i << std::endl;
    }

    // II. In maximally generic code, containers might not provide begin() and 
    // end() methods but these methods would be defined as non-member functions.
    std::cout << "first element: " << *(::cbegin (numbers)) << std::endl;   // 3
    std::cout << "last element: " << *(::cend (numbers) - 1) << std::endl;  // 11, because we appended that

    return 0;
}