## **Arguments agains raw pointers**

1) A raw pointer declaration does not indicate whether the pointed element is a single object or an array of objects.
2) The declaration does not tell who *owns* the pointed object. Who should be responsible for deallocating the memory?
3) There is no way to tell how to destroy the pointed object properly. (`delete` vs. `delete[]` vs. other destuction mechanism)
4) Misusing `delete` or `delete[]` will lead to undefined behavior!
5) After establishing who the owner of the pointer is, and how to properly destroy the pointed object it is still difficult to determine whether the object will be freed *exactly __once__* on every path inside the code (including exception handling). Missing a path leads to resource leaks, and calling the destructor several times leads to undefined behavior.
6) There is no way to tell whether a pointer is a __dangling pointer__ or not. (Was the pointed object already destroyed?)

Smart pointers attempt to improve on the flaws of using raw pointers, with far fewer opportunities for error.

### There are four types of smart pointers of of C++11

- ~~std::auto_ptr~~ (*deprecated leftover from C++98*)
- std::unique_ptr
- std::shared_ptr
- std::weak_ptr

These pointers help in the different uses of raw pointers by encapsulating them, and managing the lifetimes of dynamically allocated objects (destroying them exatly once at the appropriate place).

### std::auto_ptr

This type of pointer was an attempt to improve on the usage of raw pointers. However, the problem it tried to solve required _move semantics_, which was only introduced in C++11. Therefore, its usage is was highly inapplicable, and was later replaced by **std::unique_ptr**.
