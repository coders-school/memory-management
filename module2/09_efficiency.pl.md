<!-- .slide: data-background="#111111" -->

# Wydajność

___

## Wskaźnik surowy

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

## Wskaźnik unikalny

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

## Wskaźnik współdzielony

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

## Wskaźnik współdzielony – `make_shared`

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

## Wskaźnik słaby

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
* <!-- .element: class="fragment fade-in" --> kompilacja z użyciem <code>–std=c++11 –O3 –DNDEBUG</code>
* <!-- .element: class="fragment fade-in" --> mierzenie za pomocą:
  * <!-- .element: class="fragment fade-in" --> time (real)
  * <!-- .element: class="fragment fade-in" --> htop (mem)
  * <!-- .element: class="fragment fade-in" --> valgrind (allocations count) 
  
  <!-- czy zamienić słowa w nawiasach na polskie odpowiedniki tj: time (rzeczywisty), htop (pamięć), valgrind (liczba alokacji); patrząc na ten fragment mam dylemat bo z jednej strony da się, z drugiej jednak dziwnie będzie to jakoś mi wyglądać, dlatego pozostawiam to pod osąd. -->

___

## Wynik

| Nazwa testu      | czas [s] | alokacje | pamięć [MB] |
|:--------------:|:--------:|:-----------:|:-----------:|
| raw pointer  <!-- .element: class="fragment fade-in" -->  | 0.54    <!-- .element: class="fragment fade-in" --> | 10 000 001 <!-- .element: class="fragment fade-in" --> | 686 <!-- .element: class="fragment fade-in" -->       |
| unique pointer <!-- .element: class="fragment fade-in" --> | 0.56 <!-- .element: class="fragment fade-in" -->    | 10 000 001 <!-- .element: class="fragment fade-in" --> | 686 <!-- .element: class="fragment fade-in" -->        |
| shared pointer <!-- .element: class="fragment fade-in" --> | 1.00  <!-- .element: class="fragment fade-in" -->   | 20 000 001 <!-- .element: class="fragment fade-in" --> | 1072  <!-- .element: class="fragment fade-in" -->      |
| make shared  <!-- .element: class="fragment fade-in" -->  | 0.76 <!-- .element: class="fragment fade-in" -->    | 10 000 001 <!-- .element: class="fragment fade-in" --> | 914 <!-- .element: class="fragment fade-in" -->        |
| weak pointer <!-- .element: class="fragment fade-in" -->  | 1.28  <!-- .element: class="fragment fade-in" -->   | 20 000 002 <!-- .element: class="fragment fade-in" --> | 1222 <!-- .element: class="fragment fade-in" -->       |

___

## Konkluzje

* <!-- .element: class="fragment fade-in" --> RAII
  * <!-- .element: class="fragment fade-in" --> pozyskanie zasobów w konstruktorze
  * <!-- .element: class="fragment fade-in" --> zwolnienie zasobów w destruktorze
* <!-- .element: class="fragment fade-in" --> Reguła 5, Reguła 0
* <!-- .element: class="fragment fade-in" --> Inteligentne wskaźniki:
  * <!-- .element: class="fragment fade-in" --> <code>std::unique_ptr</code> – podstawowy wybór, bez narzutów, można przekonwertować na <code>std::shared_ptr</code>
  * <!-- .element: class="fragment fade-in" --> <code>std::shared_ptr</code> – wprowadza narzut pamięci i czasu wykonywania
  * <!-- .element: class="fragment fade-in" --> <code>std::weak_ptr</code> – łamanie cykli, można konwertować do/z <code>std::shared_ptr</code>
* <!-- .element: class="fragment fade-in" --> Tworzy inteligentne wskaźniki za pomocą <code>std::make_shared()</code> i <code>std::make_unique()</code>
* <!-- .element: class="fragment fade-in" --> Surowy wskaźnik powinien oznaczać „tylko dostęp” (brak własności)
* <!-- .element: class="fragment fade-in" --> Jeśli to możliwe, używaj odwołań zamiast wskaźników
