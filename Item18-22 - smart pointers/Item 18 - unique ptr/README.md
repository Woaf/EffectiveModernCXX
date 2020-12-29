## Unique pointers

std::unique_ptr explicitly declare their exclusive ownership on an object. Their operations execute about the same instructions as raw pointers (such as dereferencing). 

If a certain pbject requires customized destruction, then a custom deleter function may be provided to the std::unique_ptr. The deleter function may take the form of a lambda expression, or a function pointer. 

The size of the std::unique_ptr depends on whether the custom deleter function is a stateful lambda expression (in which case the size of the stored state is added to the size of the pointer). If applicable, a stateless deleter function in the form of a lambda expression is preferred.