# Define special member function in implementation file, when using Pimpl Idiom

Usually, classes are defined in a header file, and its member functions in a separate implementation file. If a certain class uses another user defined class as a member, then its header must be included in the header file. If the included header file is prone to change frequently, then all client code (that includes the said header file) *must be recompiled* recursively. This may cause an unncessarily big compilation time. 

A class can have a pointer to an *incomplete type*, aka a pre-declared class / struct, which then can be defined in the implementation file. 


