<!-- .slide: data-background="#111111" -->

# Wydajność

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

## Pomiary

* <!-- .element: class="fragment fade-in" --> gcc-4.8.2
* <!-- .element: class="fragment fade-in" --> kompilacja z <code>–std=c++11 –O3 –DNDEBUG</code>
* <!-- .element: class="fragment fade-in" --> pomiary z wykorzystaniem:
  * <!-- .element: class="fragment fade-in" --> time (real)
  * <!-- .element: class="fragment fade-in" --> htop (mem)
  * <!-- .element: class="fragment fade-in" --> valgrind (liczba alokacji)

___

## Wyniki

| test name      | time [s] | allocations | memory [MB] |
|:--------------:|:--------:|:-----------:|:-----------:|
| raw pointer  <!-- .element: class="fragment fade-in" -->  | 0.54    <!-- .element: class="fragment fade-in" --> | 10 000 001 <!-- .element: class="fragment fade-in" --> | 686 <!-- .element: class="fragment fade-in" -->       |
| unique pointer <!-- .element: class="fragment fade-in" --> | 0.56 <!-- .element: class="fragment fade-in" -->    | 10 000 001 <!-- .element: class="fragment fade-in" --> | 686 <!-- .element: class="fragment fade-in" -->        |
| shared pointer <!-- .element: class="fragment fade-in" --> | 1.00  <!-- .element: class="fragment fade-in" -->   | 20 000 001 <!-- .element: class="fragment fade-in" --> | 1072  <!-- .element: class="fragment fade-in" -->      |
| make shared  <!-- .element: class="fragment fade-in" -->  | 0.76 <!-- .element: class="fragment fade-in" -->    | 10 000 001 <!-- .element: class="fragment fade-in" --> | 914 <!-- .element: class="fragment fade-in" -->        |
| weak pointer <!-- .element: class="fragment fade-in" -->  | 1.28  <!-- .element: class="fragment fade-in" -->   | 20 000 002 <!-- .element: class="fragment fade-in" --> | 1222 <!-- .element: class="fragment fade-in" -->       |

___

## Podsumowanie

* <!-- .element: class="fragment fade-in" --> RAII
  * <!-- .element: class="fragment fade-in" --> pozyskujemy zasób w konstruktorze
  * <!-- .element: class="fragment fade-in" --> zwalniamy zasów w destruktorze
* <!-- .element: class="fragment fade-in" --> Rule of 5, Rule of 0
* <!-- .element: class="fragment fade-in" --> Smart pointery:
  * <!-- .element: class="fragment fade-in" --> <code>std::unique_ptr</code> – główny wybór, brak dodatkowych kosztów, można go skonwertować na <code>std::shared_ptr</code>
  * <!-- .element: class="fragment fade-in" --> <code>std::shared_ptr</code> – wprowadza dodatkowy narzut pamięciowy i czasu wykonania
  * <!-- .element: class="fragment fade-in" --> <code>std::weak_ptr</code> – do łamania cykli, konwertuje się z/na <code>std::shared_ptr</code>
* <!-- .element: class="fragment fade-in" --> Twórz smart pointery używając <code>std::make_shared()</code> i <code>std::make_unique()</code>
* <!-- .element: class="fragment fade-in" --> Zwykłe wskaźniki powinny zawsze oznaczać tylko dostęp do zasobu (bez własności)
* <!-- .element: class="fragment fade-in" --> Kiedy to możliwe używaj referencji zamiast jakichkolwiek wskaźników
