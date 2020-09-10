# Memory management

## Linux compilation

    > mkdir build
    > cd build
    > cmake ..
    > make

## Valgrind usage

    > valgrind valgrind_params path/to/binary binary_params, eg:
    > valgrind --leak-check=full ./ResourceD 5

## Memory management problems

1. Compile and run under valgrind all applications from examples directory
2. Check valgrind errors

## Exercises

### ResourceD

1. Compile and run ResourceD application and check memory leaks under valgrind
2. Fix memory leaks with a proper usage of delete operator
3. Refactor the solution to use `std::unique_ptr<>`
4. Use `std::make_unique`

### ResourceFactory

1. Compile and run ResourceFactory application
2. Put comments in places where you can spot some problems
3. How to remove elements from the collection (`vector<Resource*> resources`)?
4. Check memory leaks
5. Fix problems

### List

Take a look at List.cpp file, where simple (and buggy) single-linked list is implemented.
    `void add(Node* node)` method adds a new Node at the end of the list
    `Node* get(const int value)` method iterate over the list and returns the first Node with matching value or nullptr

1. Compile and run List application
2. Fix memory leaks without introducing smart pointers
3. Fix memory leaks with smart pointers. What kind of pointers needs to be applied and why?
4. What happens when the same Node is added twice? Fix this problem.
5. (Optional) Create `EmptyListError` exception (deriving from `std::runtime_error`). Add throwing and catching it in a proper places.

## Post-work

You can work in groups or individually. Please fork the repo and submit a Pull Request after you have finished.

1. Transform the list from List.cpp into double-linked list. You should implement:
    - inserting Nodes at the beginning of the list
    - searching elements from the backward
Apply proper smart pointers for the reverse direction.

2. Implement your own unique_ptr. Requirements:
    - Templatized (should hold a pointer to a template type)
    - RAII (acquire in constructor, release in destructor)
    - Copying not allowed
    - Moving allowed
    - Member functions: `operator*()`, `operator->()`, `get()`, `release()`, `reset()`

3. Read one of these articles on move semantics:
    - [Semantyka przenoszenia](https://infotraining.bitbucket.io/cpp-11/move.html) (in Polish)
    - [Move semantics and rvalue references in C++11](https://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html) (in English)