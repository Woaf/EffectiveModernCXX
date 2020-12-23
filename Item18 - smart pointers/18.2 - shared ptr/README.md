## Shared pointers

"An object accessed via an std::shared_ptr has its lifetime managed by those pointers through shared ownership." Destruction of the object happens only when the object is no longer needed. 

A shared pointer stores the number of pointers pointing to the object. With each new pointer pointing to it, this counter is incremented; and in similar fashion, it is decremented, when a pointer no longer points to the object (aka, when it's constructor runs). Once this counter reaches zero, the object is freed from the heap.