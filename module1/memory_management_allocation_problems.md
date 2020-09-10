<!-- .slide: data-background="#111111" -->

# Dynamic allocation problems

## Quiz

___

## What kind of problem is here? #1

```cpp
#include <iostream>

int main() {
    const auto size = 10;
    int* dynamicArray = new int[size];

    for (int i = 0; i <= size; ++i) {
        *(dynamicArray + i) = i * 10;
    }

    for (int i = 0; i <= size; ++i) {
        std::cout << dynamicArray[i] << '\n';
    }

    delete[] dynamicArray;
}
```
<!-- .element: class="fragment fade-in" -->

### Accessing out-of-bounds memory
<!-- .element: class="fragment fade-in" -->

___

## What kind of problem is here? #2

```cpp
#include <iostream>

struct Msg {
    int value{100};
};

void processMsg(Msg* msg) {
    std::cout << msg->value << '\n';
}

int main() {
    Msg* m = new Msg();
    delete m;
    processMsg(m);
    return 0;
}
```

### Dangling pointer
<!-- .element: class="fragment fade-in" -->

A pointer which indicates to something that is not valid
<!-- .element: class="fragment fade-in" -->

___

## What kind of problem is here? #3

```cpp
class Msg {};

void processMsg(Msg* msg) {
    // ...
    delete msg;
}

int main() {
    Msg* m = new Msg{};
    processMsg(m);
    delete m;
}
```

### Double delete
<!-- .element: class="fragment fade-in" -->

Happens when a dangling pointer is deleted
<!-- .element: class="fragment fade-in" -->

___

## What kind of problem is here? #4

```cpp
#include <iostream>

int main() {
    int* p = new int{10};
    delete p;
    p = nullptr;

    std::cout << *p << '\n';

    return 0;
}
```

### Null pointer dereference
<!-- .element: class="fragment fade-in" -->

Happens when a `nullptr` is used
<!-- .element: class="fragment fade-in" -->

___

## What kind of problem is here? #5

```cpp
class Msg {};

void processMsg(Msg* msg) {
    // ...
    delete msg;
}

int main() {
    Msg m;
    processMsg(&m);

    return 0;
}
```

### Freeing stack allocated blocks
<!-- .element: class="fragment fade-in" -->

___

## What kind of problem is here? #6

```cpp
int main() {
    constexpr auto size = 4u;
    int* array = new int[size]{1, 2, 3, 4};
    delete array;

    return 0;
}
```

### Freeing a portion of a dynamic block
<!-- .element: class="fragment fade-in" -->

Using `delete` instead of `delete[]`
<!-- .element: class="fragment fade-in" -->

___

## What kind of problem is here? #7

```cpp
#include <iostream>

int main() {
    int* p = new int{10};
    p = new int{20};
    std::cout << *p << '\n';
    delete p;

    return 0;
}
```

### Memory leak
<!-- .element: class="fragment fade-in" -->

Allocated memory which cannot be freed because there is no pointer that points to it
<!-- .element: class="fragment fade-in" -->

___

## Dynamic allocation problems

* <!-- .element: class="fragment fade-in" --> accessing out-of-bounds memory
* <!-- .element: class="fragment fade-in" --> dangling pointer
* <!-- .element: class="fragment fade-in" --> double deleting
* <!-- .element: class="fragment fade-in" --> <code>null</code> pointer dereference
* <!-- .element: class="fragment fade-in" --> freeing memory blocks that were not dynamically allocated
* <!-- .element: class="fragment fade-in" --> freeing a portion of a dynamic block
* <!-- .element: class="fragment fade-in" --> memory leak

All allocation problems cause Undefined Behavior.
<!-- .element: class="fragment fade-in" -->

These problems can be addressed by ASAN (Address Sanitizer) or Valgrind.
Unfortunately they do not work on Windows 😕
<!-- .element: class="fragment fade-in" -->
