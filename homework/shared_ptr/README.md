### This branch contains the complete implementation of
* `shared_ptr`
* `weak_ptr`
* `make_shared`

#### `shared_ptr` is a RAII class:
* Holds a pointer to managed object (template class)
* Holds a pointer to shared control block with 2 counters and a deleter:
  * shared_refs count (as `std::atomic<size_t>`)
  * weak_refs count (as `std::atomic<size_t>`)
  * deleter (function pointer)
* Constructor copies a pointer and allocates the control block:
  * can be created with a custom deleter
  * when created from expired `weak_ptr` throws `bad_weak_ptr` exception
  * when desired memory cannot be allocated it makes sure that no memory leaks are possible by releasing memory
* Destructor decreases shared_refs and:
  * if shared_refs == 0 -> releases the managed object
  * if shared_refs == 0 and weak_refs == 0 -> releases the control block
* Copying is allowed - it increments shared_refs
* Moving is allowed and it means:
  * Copying original pointers to a new object
  * Setting source pointer to nullptr
* Member functions: `operator*()`, `operator->()`, `get()`, `reset()`, `use_count()`, `operator bool()`

#### `weak_ptr`:
* Proper cooperation with `shared_ptr`
  * can be created from `shared_ptr`
  * constructor increments weak_ref count
  * destructor:
    * decrements weak_ref count
    * if weak_ref count == 0 and shared_ref count == 0 -> releases control block
  * copying is allowed - it increments weak_refs
  * moving is allowed and it means:
    * copying original pointers to a new object
    * setting source pointer to nullptr
* Member functions: `use_count()`, `expired()`, `lock()`, `reset()`

#### `make_shared`:
  * creates a `shared_ptr` of a given type
  * uses variadic templates to take any number of parameters
  * first template parameter type is the underlying object type
  * other template parameters are passed via perfect forwarding to the constructor of a given type
  * reduces the number of memory allocations to 1 while creating `shared_ptr` by:
    * creating control block that contains the managed object
    * such control block inherits after the default control block
    * such control block uses polymorphism to indicate that it contains the object
    
Additionally there is CI:
 * checks if everything compiles
 * runs Unit Tests for every suite
 * runs Valgrind memory checks


