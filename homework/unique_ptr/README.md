# `unique_ptr`

(30 XP) Implement your own unique_ptr (simplified).

unique_ptr is a RAII class:

* Holds a pointer to managed object (template class)
* V Constructor copies a pointer
* V Destructor release memory
* V Copying is not allowed
* V Moving is allowed and it means:
  * V Copying original pointer to a new object
  * V Setting source pointer to nullptr
* Member functions:V  operator*(), V operator->(), get(), release(), reset()
* V   Should be implemented in `unique_ptr.hpp` file inside `my` namespace
* V   Tests should be written inside `unique_ptr_tests.cpp` using GoogleTest or Catch2
* You should instantiate `unique_ptr` template class in `unique_ptr_tests.cpp` above your test cases, e.g. `template class my::unique_ptr<int>;` It's needed for code coverage check to work properly.
