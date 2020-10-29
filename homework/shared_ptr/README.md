### `make_shared`

This branch contains the complete implementation of
* `shared_ptr`
* `weak_ptr`
* `make_shared`

Features:
* `make_shared`:
  * creates a `shared_ptr` of a given type
  * uses variadic templates to take any number of parameters
  * first template parameter type is the underlying object type
  * other template parameters are passed via perfect forwarding to the constructor of a given type
  * reduces the number of memory allocations to 1 while creating `shared_ptr` by
    * creating controlBlock that contains the managed object
    * such controlBlock inherits after the default controlBlock
    * such controlBlock uses polymorphism to indicate that it contains the object

* `shared_ptr`:
  * can be created with a custom deleter
  * when created from expired `weak_ptr` throws `bad_weak_ptr` exception
  * when desired memory cannot be allocated it makes sure that no memory leaks are possible by releasing memory
