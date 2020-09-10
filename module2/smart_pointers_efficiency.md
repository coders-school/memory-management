<!-- .slide: data-background="#111111" -->

# Efficiency

___

## Raw pointer

```cpp
#include <memory>
#include <vector>

struct Data {
    char tab_[42];
};

int main(void) {
    constexpr unsigned size = 10u * 1000u * 1000u;
    std::vector<Data *> v;
    v.reserve(size);
    for (unsigned i = 0; i < size; ++i) {
        auto p = new Data;
        v.push_back(std::move(p));
    }
    for (auto p: v)
        delete p;
}
```

___

## Unique pointer

```cpp
#include <memory>
#include <vector>

struct Data {
    char tab_[42];
};

int main(void) {
    constexpr unsigned size = 10u * 1000u * 1000u;
    std::vector<std::unique_ptr<Data>> v;
    v.reserve(size);
    for (unsigned i = 0; i < size; ++i) {
        std::unique_ptr<Data> p{new Data};
        v.push_back(std::move(p));
    }
}
```

___

## Shared pointer

```cpp
#include <memory>
#include <vector>

struct Data {
    char tab_[42];
};

int main(void) {
    constexpr unsigned size = 10u * 1000u * 1000u;
    std::vector<std::shared_ptr<Data>> v;
    v.reserve(size);
    for (unsigned i = 0; i < size; ++i) {
        std::shared_ptr<Data> p{new Data};
        v.push_back(std::move(p));
    }
}
```

___

## Shared pointer – `make_shared`

```cpp
#include <memory>
#include <vector>

struct Data {
    char tab_[42];
};

int main(void) {
    constexpr unsigned size = 10u * 1000u * 1000u;
    std::vector<std::shared_ptr<Data>> v;
    v.reserve(size);
    for (unsigned i = 0; i < size; ++i) {
        auto p = std::make_shared<Data>();
        v.push_back(std::move(p));
    }
}
```

___

## Weak pointer

```cpp
#include <memory>
#include <vector>

struct Data {
    char tab_[42];
};

int main(void) {
    constexpr unsigned size = 10u * 1000u * 1000u;
    std::vector<std::shared_ptr<Data>> vs;
    std::vector<std::weak_ptr<Data>> vw;
    vs.reserve(size);
    vw.reserve(size);
    for (unsigned i = 0; i < size; ++i) {
        std::shared_ptr<Data> p{new Data};
        std::weak_ptr<Data> w{p};
        vs.push_back(std::move(p));
        vw.push_back(std::move(w));
    }
}
```

___

## Measurements

* <!-- .element: class="fragment fade-in" --> gcc-4.8.2
* <!-- .element: class="fragment fade-in" --> compilation with <code>–std=c++11 –O3 –DNDEBUG</code>
* <!-- .element: class="fragment fade-in" --> measuring with:
  * <!-- .element: class="fragment fade-in" --> time (real)
  * <!-- .element: class="fragment fade-in" --> htop (mem)
  * <!-- .element: class="fragment fade-in" --> valgrind (allocations count)

___

## Results

| test name      | time [s] | allocations | memory [MB] |
|:--------------:|:--------:|:-----------:|:-----------:|
| raw pointer  <!-- .element: class="fragment fade-in" -->  | 0.54    <!-- .element: class="fragment fade-in" --> | 10 000 001 <!-- .element: class="fragment fade-in" --> | 686 <!-- .element: class="fragment fade-in" -->       |
| unique pointer <!-- .element: class="fragment fade-in" --> | 0.56 <!-- .element: class="fragment fade-in" -->    | 10 000 001 <!-- .element: class="fragment fade-in" --> | 686 <!-- .element: class="fragment fade-in" -->        |
| shared pointer <!-- .element: class="fragment fade-in" --> | 1.00  <!-- .element: class="fragment fade-in" -->   | 20 000 001 <!-- .element: class="fragment fade-in" --> | 1072  <!-- .element: class="fragment fade-in" -->      |
| make shared  <!-- .element: class="fragment fade-in" -->  | 0.76 <!-- .element: class="fragment fade-in" -->    | 10 000 001 <!-- .element: class="fragment fade-in" --> | 914 <!-- .element: class="fragment fade-in" -->        |
| weak pointer <!-- .element: class="fragment fade-in" -->  | 1.28  <!-- .element: class="fragment fade-in" -->   | 20 000 002 <!-- .element: class="fragment fade-in" --> | 1222 <!-- .element: class="fragment fade-in" -->       |

___

## Conclusions

* <!-- .element: class="fragment fade-in" --> RAII
  * <!-- .element: class="fragment fade-in" --> acquire resource in constructor
  * <!-- .element: class="fragment fade-in" --> release resource in destructor
* <!-- .element: class="fragment fade-in" --> Rule of 5, Rule of 0
* <!-- .element: class="fragment fade-in" --> Smart pointers:
  * <!-- .element: class="fragment fade-in" --> <code>std::unique_ptr</code> – primary choice, no overhead, can convert to <code>std::shared_ptr</code>
  * <!-- .element: class="fragment fade-in" --> <code>std::shared_ptr</code> – introduces memory and runtime overhead
  * <!-- .element: class="fragment fade-in" --> <code>std::weak_ptr</code> – breaking cycles, can convert to/from <code>std::shared_ptr</code>
* <!-- .element: class="fragment fade-in" --> Create smart pointers with <code>std::make_shared()</code> and <code>std::make_unique()</code>
* <!-- .element: class="fragment fade-in" --> Raw pointer should mean „access only” (no ownership)
* <!-- .element: class="fragment fade-in" --> Use reference instead of pointers if possible
