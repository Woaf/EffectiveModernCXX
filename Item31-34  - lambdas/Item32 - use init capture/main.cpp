#include <memory>
#include "classes.hpp"

int main () 
{
    // auto pw = std::make_unique<Widget> (); // unnecessary, if it is passed to the lambda right after
    
    auto func = [pw = std::make_unique<Widget> ()] {
                    return pw->isValidated () && pw->isArchived (); 
                };

    return 0;
}
