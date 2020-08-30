<!-- .slide: data-background="#111111" -->

# `std::unique_ptr<>`

___

## `std::unique_ptr<>`

### Cechy

* <!-- .element: class="fragment fade-in" --> jeden obiekt == jeden właściciel
* <!-- .element: class="fragment fade-in" --> destruktor niszczy obiekt
* <!-- .element: class="fragment fade-in" --> kopiowanie niedozwolone
* <!-- .element: class="fragment fade-in" --> przemieszczanie dozwolone
* <!-- .element: class="fragment fade-in" --> można użyć niestandardowego usuwania

<img data-src="img/uniqueptrinverted.png" alt="unique pointers" class="plain fragment fade-in">

___

### użycie `std::unique_ptr<>`

* Podejście w starym stylu kontra nowoczesne podejście

<div class="multicolumn">
<div class="col">

```cpp
#include <iostream> // podejście w starym stylu


struct Msg {
    int getValue() { return 42; }
};

Msg* createMsg() {
    return new Msg{};
}

int main() {
    auto msg = createMsg();

    std::cout << msg->getValue();
    delete msg;
}
```
<!-- .element: class="fragment fade-in" -->

</div>

<div class="col">

```cpp
#include <memory> // podejście nowoczesne
#include <iostream>

struct Msg {
    int getValue() { return 42; }
};

std::unique_ptr<Msg> createMsg() {
    return std::make_unique<Msg>();
}

int main() {
    // unique ownership
    auto msg = createMsg();

    std::cout << msg->getValue();
}

```
<!-- .element: class="fragment fade-in" -->

</div>

___

### użycie `std::unique_ptr<>`

* <!-- .element: class="fragment fade-in" --> Kopiowanie nie jest dozwolone
* <!-- .element: class="fragment fade-in" --> Przemieszczanie jest dozwolone

<div class="multicolumn">
<div class="col">

```cpp
std::unique_ptr<MyData> source(void);
void sink(std::unique_ptr<MyData> ptr);

void simpleUsage() {
    source();
    sink(source());
    auto ptr = source();
    // sink(ptr);       // błąd kompilacji
    sink(std::move(ptr));
    auto p1 = source();
    // auto p2 = p1;    // błąd kompilacji
    auto p2 = std::move(p1);
    // p1 = p2;         // błąd kompilacji
    p1 = std::move(p2);
}
```
<!-- .element: class="fragment fade-in" -->

</div>

<div class="col">

```cpp
std::unique_ptr<MyData> source(void);
void sink(std::unique_ptr<MyData> ptr);

void collections() {
    std::vector<std::unique_ptr<MyData>> v;
    v.push_back(source());

    auto tmp = source();
    // v.push_back(tmp); // błąd kompilacji
    v.push_back(std::move(tmp));

    // sink(v[0]);       // błąd kompilacji
    sink(std::move(v[0]));

}
```
<!-- .element: class="fragment fade-in" -->

</div>

___

#### Współpraca `std::unique_ptr<>` z surowymi wskaźnikami

```cpp
#include <memory>

void legacyInterface(int*) {}
void deleteResource(int* p) { delete p; }
void referenceInterface(int&) {}

int main() {
    auto ptr = std::make_unique<int>(5);
    legacyInterface(ptr.get());
    deleteResource(ptr.release());
    ptr.reset(new int{10});
    referenceInterface(*ptr);
    ptr.reset(); // ptr jest nullptr
    return 0;
}
```

* <!-- .element: class="fragment fade-in" --> <code>get()</code> – zwraca surowy wskaźnik bez zwalniania własności
* <!-- .element: class="fragment fade-in" --> <code>release()</code> – zwraca surowy wskaźnik i zwalnia własność
* <!-- .element: class="fragment fade-in" --> <code>reset()</code> – zastępuje obiekt menedżera
* <!-- .element: class="fragment fade-in" --> <code>operator*()</code> – wyłuskuje wskaźnik do zarządzanego obiektu

___

### `std::make_unique()`

```cpp
#include <memory>

struct Msg {
    Msg(int i) : value(i) {}
    int value;
};

int main() {
    auto ptr1 = std::unique_ptr<Msg>(new Msg{5});
    auto ptr2 = std::make_unique<Msg>(5);   // równoznaczne z powyższym
    return 0;
}
```

`std::make_unique()` jest funkcją fabryczną, która generuje `unique_ptrs`
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> dodane w C++14 do symetrycznych operacji na unikalnych i wspólnych wskaźnikach
* <!-- .element: class="fragment fade-in" --> unika czystego wyrażenia <code>new</code>

___

### `std::unique_ptr<T[]>`

```cpp
struct MyData {};

void processPointer(MyData* md) {}
void processElement(MyData md) {}

using Array = std::unique_ptr<MyData[]>;

void use(void)
{
    Array tab{new MyData[42]};
    processPointer(tab.get());
    processElement(tab[13]);
}
```

* <!-- .element: class="fragment fade-in" --> Podczas niszczenia
  * <!-- .element: class="fragment fade-in" --> <code>std::unique_ptr&ltT&gt</code> wywołuje <code>delete</code>
  * <!-- .element: class="fragment fade-in" --> <code>std::unique_ptr&ltT[]&gt</code> wywołuje <code>delete[]</code>
* <!-- .element: class="fragment fade-in" --> <code>std::unique_ptr&ltT[]&gt</code> ma dodatkowy <code>operator[]</code> umożliwiający dostęp do elementu tablicy
* <!-- .element: class="fragment fade-in" --> Zwykle lepszym wyborem jest <code>std::vector&ltT&gt</code>

___

## Ćwiczenie: ResourceD

1. <!-- .element: class="fragment fade-in" --> Skompiluj i uruchom aplikację ResourceD
2. <!-- .element: class="fragment fade-in" --> Sprawdź wycieki pamięci pod valgrind
3. <!-- .element: class="fragment fade-in" --> Napraw wycieki pamięci, używając właściwego operatora <code>delete</code>
4. <!-- .element: class="fragment fade-in" --> Zrefaktoryzuj rozwiązanie, aby użyć <code>std::unique_ptr<></code>
5. <!-- .element: class="fragment fade-in" --> Użyj <code>std::make_unique()</code>
