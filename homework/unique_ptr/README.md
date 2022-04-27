# `unique_ptr`

(36 XP) Implement your own unique_ptr (simplified).

unique_ptr is a RAII class:

* Holds a pointer to managed object (template class)
* Constructor copies a pointer
* Destructor release memory
* Copying is not allowed
* Moving is allowed and it means:
  * Copying original pointer to a new object
  * Setting source pointer to nullptr
* Member functions: operator*(), operator->(), get(), release(), reset()
* Should be implemented in `unique_ptr.hpp` file inside `my` namespace
* Tests should be written inside `unique_ptr_tests.cpp` using GoogleTest or Catch2
* You should instantiate `unique_ptr` template class in `unique_ptr_tests.cpp` above your test cases, e.g. `template class my::unique_ptr<int>;` It's needed for code coverage check to work properly.
