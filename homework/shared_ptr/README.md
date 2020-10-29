### `make_shared`

Implementation of my `make_shared` function.

Features:

* creates a `shared_ptr` of a given type
* uses variadic templates to take any number of parameters
* first template parameter type is the underlying object type
* other template parameters are passed via perfect forwarding to the constructor of a given type
* optimized memory layout of `shared_ptr` created by `make_shared` by reducing the number of memory allocations to 1

