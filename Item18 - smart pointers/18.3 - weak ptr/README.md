# std::weak_ptr

Weak pointers act like `std::shared_ptr`s, with the exception that they can point to object which might have been already destroyed. In a way, `std::weak_ptr` is just like `std::shared_ptr` that does not change the object's reference count.

A weak pointer cannot be dereferenced not it can be tested for nullness - it is an *augmentation* of the std::shared_ptr.

Weak pointers are created from shared pointers. They point to the same object, but do not modify the reference count.

We may check if the weak pointer points to a non-deleted object with its `.expired ()` method. It would be most desireable to try to access the pointed object knowing whether it still points to a valid object in the memory. However, *if it would be possible*, dereferencing the object via its weak pointer might cause a race condition. A process from another thread might delete the pointed object while we try to dereference it through its weak pointer. This would lead to *undefined behavior*, but most probably a crash.

For that to be avoided, C++ introduces an *atomic operation* called `lock ()`, which creates a shared pointer if the weak pointer is not yet expired. `nullptr` is returned if the weak pointer was expired. There are two ways of acquiring a shared pointer from a weak pointer. 

- One way of doing it is to use the `lock ()` method
- Another way is to pass the weak poiner as constructor argument of the shared pointer. In this case, if the shared pointer was expired, then an `std::bad_weak_ptr` exception is thrown.

### Summary

Use std::weak_ptr for pointers that can dangle, but should act like std::shared_ptr

Use std::weak_ptr for caching, observer-like mechanisms, and the prevention of std::shared_ptr cycles.

### Personal addendum

The std::weak_ptr may come in very handy in game development, when we are keeping track of destroyable or killable entities in a scene. Such objects may be declared using shared pointers, and their observer counterparts may refer to these object via weak pointers. Killed or destroyed objects may not need to be obliterated immediately from memory, but sometime later during the game cycle (i.e. the player moving far away from the said object, or after a ceratin amount of time), where a custom garbage-collector-like algorithm may clear up these objects.
