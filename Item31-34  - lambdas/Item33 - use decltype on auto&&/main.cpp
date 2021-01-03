#include <iostream>
#include <functional>

int main () 
{
    auto f = [] (auto&&... param) {
        return someFunction (normalize (std::forward<decltype (param)> (param)...));
    };

    return 0;
}