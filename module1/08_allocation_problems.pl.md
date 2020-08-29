<!-- .slide: data-background="#111111" -->

# Problemy z alokacją dynamiczną

## Quiz

___

## Jaki rodzaj problemu pojawia się tutaj? #1

```cpp
#include <iostream>

int main() {
    const auto size = 10;
    int* dynamicArray = new int[size];

    for (int i = 0; i <= size; ++i)
        *(dynamicArray + i) = i * 10;

    for (int i = 0; i <= size; ++i)
        std::cout << dynamicArray[i] << '\n';

    delete[] dynamicArray;
}
```
<!-- .element: class="fragment fade-in" -->

### Dostęp do pamięci spoza zakresu
<!-- .element: class="fragment fade-in" -->

___

## Jaki rodzaj problemu pojawia się tutaj? #2

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

### Wiszący wskaźnik
<!-- .element: class="fragment fade-in" -->

Wskaźnik wskazujący na coś, co jest nieprawidłowe
<!-- .element: class="fragment fade-in" -->

___

## Jaki rodzaj problemu pojawia się tutaj? #3

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

### Podwójne usunięcie
<!-- .element: class="fragment fade-in" -->

Dzieje się tak, gdy wiszący wskaźnik zostanie usunięty
<!-- .element: class="fragment fade-in" -->

___

## Jaki rodzaj problemu pojawia się tutaj? #4

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

### Wyłuskiwanie wskaźnika zerowego
<!-- .element: class="fragment fade-in" -->

Dzieje się tak, gdy użyto `nullptr`
<!-- .element: class="fragment fade-in" -->

___

## Jaki rodzaj problemu pojawia się tutaj? #5

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

### Zwalnianie bloków przydzielonych na stosie
<!-- .element: class="fragment fade-in" -->

___

## Jaki rodzaj problemu pojawia się tutaj? #6

```cpp
int main() {
    constexpr auto size = 4u;
    int* array = new int[size]{1, 2, 3, 4};
    delete array;

    return 0;
}
```

### Zwalnianie części bloku dynamicznego
<!-- .element: class="fragment fade-in" -->

Użycie `delete` zamiast `delete[]`
<!-- .element: class="fragment fade-in" -->

___

## Jaki rodzaj problemu pojawia się tutaj? #7

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

### Wyciek pamięci
<!-- .element: class="fragment fade-in" -->

Przydzielona pamięć, której nie można zwolnić, ponieważ nie ma na nią wskaźnika
<!-- .element: class="fragment fade-in" -->

___

## Problemy z alokacją dynamiczną

* <!-- .element: class="fragment fade-in" --> dostęp do pamięci spoza zakresu
* <!-- .element: class="fragment fade-in" --> wiszący wskaźnik
* <!-- .element: class="fragment fade-in" --> podwójne usuwanie
* <!-- .element: class="fragment fade-in" --> wyłuskiwanie wskaźnika <code>null</code>
* <!-- .element: class="fragment fade-in" --> zwalnianie bloków pamięci, które nie zostały przydzielone dynamicznie
* <!-- .element: class="fragment fade-in" --> zwolnienie części bloku dynamicznego
* <!-- .element: class="fragment fade-in" --> wyciek pamięci

Wszystkie problemy z alokacją powodują Niezdefiniowane Zachowanie.
<!-- .element: class="fragment fade-in" -->

Problemy te można rozwiązać za pomocą ASAN (Address Sanitizer) lub Valgrind.
Niestety nie działają one w systemie Windows 😕
<!-- .element: class="fragment fade-in" -->
