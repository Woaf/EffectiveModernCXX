#include <memory>
#include <vector>
#include <functional>
#include <algorithm>
#include "classes.hpp"

int main () 
{
    // auto pw = std::make_unique<Widget> (); // unnecessary, if it is passed to the lambda right after
    
    // C++14 - init caputre
    auto funcxx14 = [pw = std::make_unique<Widget> ()] {
                    return pw->isValidated () && pw->isArchived (); 
                };

    // C++11 - generalized lambda capture
    auto funcxx11 = IsValidAndArchived (std::make_unique <Widget> ());

    std::cout << funcxx14 () << std::endl;
    std::cout << funcxx11 () << std::endl;

    // C++14 move capture (as before)
    {
        std::vector<double> data {3, 4, 5, 6};
        auto func14 = [data = std::move (data)] {
            // use data ...
            std::for_each (data.begin (), data.end (), [] (double d) {
                std::cout << d << ", ";
            });
            std::cout << std::endl;
        };
        func14 ();
    }

    // C++11 use std::bind for move capture in lambdas
    {
        std::vector<double> data {2, 3, 4, 5};
        auto func11 = std::bind ([] (const std::vector<double>& data) {
            // use data ...
            std::for_each (data.begin (), data.end (), [] (double e) {
                std::cout << e << ", ";
            }); 
            std::cout << std::endl;
        }, std::move (data) /*or std::make_unique<Widget> ()*/);
        func11 ();
    }

    return 0;
}
