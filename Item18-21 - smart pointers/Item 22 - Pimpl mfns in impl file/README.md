# Define special member function in implementation file, when using Pimpl Idiom

Usually, classes are defined in a header file, and its member functions in a separate implementation file. If a certain class uses another user defined class as a member, then its header must be included in the header file. If the included header file is prone to change frequently, then all client code (that includes the said header file) *must be recompiled* recursively. This may cause an unncessarily big compilation time. 

A class can have a pointer to an *incomplete type*, aka a pre-declared class / struct, which then can be defined in the implementation file. 

In `commit#:b233287a14949d58bd2b76061a90b4737ab87fe3` we can see that Class includes person.h. This should not be the case, since none of the Person objects are dereferenced or called with its member functions. Therefore, it can be declared as a pointer inside the class declaration. Furthermore, this can be generalized to all data members of the Class data members. We can declare an implementation structure that will contain all of the data members of Class.


