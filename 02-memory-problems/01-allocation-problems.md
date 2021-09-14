<!-- .slide: data-background="#111111" -->

# Problemy z pamięcią

## Quiz

___

## Jaki tu jest problem? #1

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

### Dostęp do pamięci poza zakresem tablicy
<!-- .element: class="fragment fade-in" -->

___

## Jaki tu jest problem? #2

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

### Wiszący wskaźnik (ang. dangling pointer)
<!-- .element: class="fragment fade-in" -->

Wskaźnik, który pokazuje na niepoprawną (np. usuniętą) pamięć
<!-- .element: class="fragment fade-in" -->

___

## Jaki tu jest problem? #3

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

### Podwójne usuwanie (ang. Double delete)
<!-- .element: class="fragment fade-in" -->

Występuje gdy usuwamy wiszący wskaźnik
<!-- .element: class="fragment fade-in" -->

___

## Jaki tu jest problem? #4

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

Występuje, gdy próbujemy wyłuskać `nullptr`
<!-- .element: class="fragment fade-in" -->

___

## Jaki tu jest problem? #5

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

### Zwalnianie pamięci zaalokowanej na stosie
<!-- .element: class="fragment fade-in" -->

___

## Jaki tu jest problem? #6

```cpp
int main() {
    constexpr auto size = 4u;
    int* array = new int[size]{1, 2, 3, 4};
    delete array;

    return 0;
}
```

### Zwalnianie niewłaściwym operatorem delete
<!-- .element: class="fragment fade-in" -->

Używanie `delete` zamiast `delete[]`
<!-- .element: class="fragment fade-in" -->

___

## Jaki tu jest problem? #7

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

Zaalokowana pamięć, która nie może zostać zwolniona, bo nie mamy do niej wskaźnika
<!-- .element: class="fragment fade-in" -->

___

## Problemy z dynamiczną alokacją

* <!-- .element: class="fragment fade-in" --> accessing out-of-bounds memory
* <!-- .element: class="fragment fade-in" --> dangling pointer
* <!-- .element: class="fragment fade-in" --> double deleting
* <!-- .element: class="fragment fade-in" --> <code>null</code> pointer dereference
* <!-- .element: class="fragment fade-in" --> freeing memory blocks that were not dynamically allocated
* <!-- .element: class="fragment fade-in" --> freeing a portion of a dynamic block
* <!-- .element: class="fragment fade-in" --> memory leak

Wszystkie powyższe problemy powoduję niezdefiniowane zachowanie.
<!-- .element: class="fragment fade-in" -->

Można je łatwo wykryć ASANem (Address Sanitizer) lub Valgrindem.
Niestety, żadne z nich nie działa na Windowsie 😕
<!-- .element: class="fragment fade-in" -->
