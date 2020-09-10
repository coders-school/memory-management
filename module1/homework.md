# Homework

___

## Pre-work

Read one of these articles on move semantics:

* [Semantyka przenoszenia](https://infotraining.bitbucket.io/cpp-11/move.html) (in Polish)
* [Move semantics and rvalue references in C++11](https://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html) (in English)

It will be useful for a post-work ;)

___

## Post-work

(36 XP) Implement your own `unique_ptr` (simplified).

`unique_ptr` is a RAII class:

* Holds a pointer to managed object (template class)
* Constructor copies a pointer
* Destructor release memory
* Copying is not allowed
* Moving is allowed and it means:
  * Copying original pointer to a new object
  * Setting source pointer to `nullptr`
* Member functions: `operator*()`, `operator->()`, `get()`, `release()`, `reset()`

+3 XP for delivery before 20.09.2020 23:59
