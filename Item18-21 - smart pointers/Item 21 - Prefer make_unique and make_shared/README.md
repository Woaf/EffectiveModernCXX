# Prefer `std::make_unique` and `std::make_shared` to direct use of `new`

So far we only worked with calling the direct constructor of the standard unique pointer and the shared pointer, however C++14 allows us to use `std::make_unique` and `std::make_shared` for unique and shared pointers respectively. (Unfortunately, `std::make_unique` is not part of C++11, however we already created our own make_unique factory functions in the previous chapters.)

`std::make_unique` does not support custom deleters. 
