## Shared pointers

"An object accessed via an std::shared_ptr has its lifetime managed by those pointers through shared ownership." Destruction of the object happens only when the object is no longer needed. 

A shared pointer stores the number of pointers pointing to the object. With each new pointer pointing to it, this counter is incremented; and in similar fashion, it is decremented, when a pointer no longer points to the object (aka, when it's constructor runs). Once this counter reaches zero, the object is freed from the heap.

std::shared_ptr has a slight memory overhead in contrast with a raw pointer. A shared pointer stores the pointer to the object as well as a pointer to the object's reference count - therefore taking up twice the amount of space as a raw pointer.

The reference counter of the shared pointer must be dynamically allocated, implying a performance overhead (when creating new pointers to the object, or when deleting one). 

A much more significant performance overhead is the fact that the incrementation and the decrementation of the reference counter **must be atomic** to make it threadsafe. 

Creating an std::shared_ptr on an object *sometimes* increases the reference counter, but not *always*. The reason for this is *move construction*. Move construction sets the source std::shared_ptr to null, meaning it stops pointing to the object. This would mean that the reference count should be decreased. On the other hand, a new std::shared_ptr is created to point to that particular object, which implies the increase of the reference count. Overall, no manipulation is needed on the reference count, when the move stemantics enter the picture. Another implication of this is that moving a shared pointer is faster than copying them, since copying also requires the modification of the reference counter - that sits in dynamic memory storage.

Another interesting feature of the std::shared_ptr is the support for custom deleter functions - just like in the case of std::unique_ptr. A small difference is that while the type of the custom deleter is part of the type of std::unique_ptr, for std::shared_ptr it is not.

Specification: an *std::shared_ptr* stores two pointers. One points to the stored object, while the other points to a *thing* called the **control block**, which can be thought of as a table. The control block stores the following: 
- *reference count* to the number of pointers pointing to the object
- copy of the *custom deleter* (if specified)
- copy of the *custom allocator* (if specified)
- (*weak counter*, will cover it in the next Item)

A new control block is created when an std::shared_pointer is created from a raw pointer, std::make_shared is called, or when a shared pointer is constructed from a unique pointer. (In the latter scenario, the construction assumes ownership, therefore the unique pointer will be set to null.)

A problem can arouse when passing a single raw pointer for the construction of two shared pointers (pointing to the same object). This will result in the pointed object to have (at least) two control blocks. Once the reference counter of the first control block reaches zero, it will attempt to free the pointed object from the heap, and it will succeed. The problem comes from the second control block realizing the same, and attempting to deallocate the already-freed object. This will result in *undefined behavior*. As a word of advice: **avoid passing raw pointers to the std::shared_ptr constructor, and use std::make_shared instead**.

However, we might want to use custom deleters, which is not possible with std::make_shared. To avoid this problem, we just have to **avoid the creation of a raw pointer variable, and pass the pointer to the shared pointer constructor in-place with the new keyword**. By doing so, we can pass the created shared pointer as the constructor argument of the second shared pointer, which avoids the problem at hand. 


*More soon: std::enable_shared_from_this<T> (CRTP)*