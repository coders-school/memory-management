<!-- .slide: data-background="#111111" -->

# Najlepsze praktyki

___

## Najlepsze praktyki

* <!-- .element: class="fragment fade-in" --> Zasada 0, Zasada 5
* <!-- .element: class="fragment fade-in" --> Unikaj jawnego <code>new</code>
* <!-- .element: class="fragment fade-in" --> Używaj <code>std::make_shared()</code> / <code>std::make_unique()</code>
* <!-- .element: class="fragment fade-in" --> Przekazuj <code>std::shared_ptr<></code> przez <code>const&</code>
* <!-- .element: class="fragment fade-in" --> Używaj referencji zamiast wskaźników

___

## Rule of 0, Rule of 5

### Rule of 5 <!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Jeśli musisz zaimplementować jedną z poniższych funkcji:
  * <!-- .element: class="fragment fade-in" --> destructor
  * <!-- .element: class="fragment fade-in" --> copy constructor
  * <!-- .element: class="fragment fade-in" --> copy assignment operator
  * <!-- .element: class="fragment fade-in" --> move constructor
  * <!-- .element: class="fragment fade-in" --> move assignment operator
* <!-- .element: class="fragment fade-in" --> To najprawdopodobniej potrzebujesz ich wszystkich, bo ręcznie zarządzasz zasobami.

### Rule of 0 <!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Używaj wrapperów RAII, aby nie implementować żadnej z powyższych funkcji

___

## Unikaj jawnego `new`

* <!-- .element: class="fragment fade-in" --> Inteligentne wskaźniki eliminują potrzebę używania jawnie <code>delete</code>
* <!-- .element: class="fragment fade-in" --> Aby zachować symetrię, nie używajmy też <code>new</code>
* <!-- .element: class="fragment fade-in" --> Alokuj zasoby używając:
  * <!-- .element: class="fragment fade-in" --> <code>std::make_unique()</code>
  * <!-- .element: class="fragment fade-in" --> <code>std::make_shared()</code>
* <!-- .element: class="fragment fade-in" --> Jedną z metryk jakości kodu może być liczba jawnych <code>new</code> i <code>delete</code>

___

<!-- .slide: style="font-size: 0.8em" -->

### Use `std::make_shared()` / `std::make_unique()`

* <!-- .element: class="fragment fade-in" --> Jaki problem mógł tu wystąpić (przed C++17)?

```cpp
struct MyData { int value; };
using Ptr = std::shared_ptr<MyData>;
void sink(Ptr oldData, Ptr newData);

void use(void) {
    sink(Ptr{new MyData{41}}, Ptr{new MyData{42}});
}
```
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Wskazówka: ta wersja jest poprawna

```cpp
struct MyData { int value; };
using Ptr = std::shared_ptr<MyData>;
void sink(Ptr oldData, Ptr newData);

void use(void) {
    Ptr oldData{new MyData{41}};
    Ptr newData{new MyData{42}};
    sink(std::move(oldData), std::move(newData));
}
```
<!-- .element: class="fragment fade-in" -->

___

### Rozkładamy alokację

`auto p = new MyData(10);` oznacza:

* <!-- .element: class="fragment fade-in" --> zaalokowanie <code>sizeof(MyData)</code> bajtów na stercie
* <!-- .element: class="fragment fade-in" --> wywołanie konstruktora <code>MyData</code>
* <!-- .element: class="fragment fade-in" --> przypisanie adresu zaalokowanej pamięci do wskaźnika <code>p</code>

The order of evaluation of operands of almost all C++ operators (including the order of
evaluation of function arguments in a function-call expression and the order of evaluation of
the subexpressions within any expression) is **unspecified**.
<!-- .element: class="fragment fade-in box" -->

___
<!-- .slide: style="font-size: 0.77em" -->

### Nieokreślona kolejność ewaluacji

* Co gdy mamy dwie takie operacje?

| first operation (A)                           | second operation (B)                          |
| :-------------------------------------------- | :-------------------------------------------- |
| (1) allocate `sizeof(MyData)` bytes           | (1) allocate `sizeof(MyData)` bytes           |
| (2) run `MyData` constructor                  | (2) run `MyData` constructor                  |
| (3) assign address of allocated memory to `p` | (3) assign address of allocated memory to `p` |

* <!-- .element: class="fragment fade-in" --> Nieokreślona kolejność ewaluacji oznaczała, że te operacje mogły być wykonane np. w takiej kolejności:
  * A1, A2, B1, B2, A3, B3
* <!-- .element: class="fragment fade-in" --> A co, gdy B2 rzuci wyjątkiem?

___

### `std::make_shared()` / `std::make_unique()`

* <!-- .element: class="fragment fade-in" --> <code>std::make_shared()</code> / <code>std::make_unique()</code> rozwiązuje ten problem

```cpp
struct MyData{ int value; };
using Ptr = std::shared_ptr<MyData>;
void sink(Ptr oldData, Ptr newData);

void use() {
    sink(std::make_shared<MyData>(41), std::make_shared<MyData>(42));
}
```
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Naprawia problem
* <!-- .element: class="fragment fade-in" --> Nie powtarzamy konstruowanego typu w kodzie
* <!-- .element: class="fragment fade-in" --> Nie używamy jawnie <code>new</code>
* <!-- .element: class="fragment fade-in" --> Optymalizujemy zużycie pamięci i ułożenie danych (tylko w przypadku <code>std::make_shared()</code>)

___

## Przekazywanie `std::shared_ptr<>`

```cpp
void foo(std::shared_ptr<MyData> p);

void bar(std::shared_ptr<MyData> p) {
    foo(p);
}
```

* <!-- .element: class="fragment fade-in" --> kopiowanie wymaga inkrementacji / dekrementacji liczników
* <!-- .element: class="fragment fade-in" --> musi być bezpieczne wielowątkowo - <code>std::atomic</code> / <code>std::lock</code> nie są darmowe
* <!-- .element: class="fragment fade-in" --> zawoła destruktory

##### Czy można lepiej?
<!-- .element: class="fragment fade-in" -->

___

## Przekazywanie `std::shared_ptr<>`

```cpp
void foo(const std::shared_ptr<MyData> & p);

void bar(const std::shared_ptr<MyData> & p) {
    foo(p);
}
```

* <!-- .element: class="fragment fade-in" --> tak szybkie jak przekazywanie zwykłego wskaźnika
* <!-- .element: class="fragment fade-in" --> bez dodatkowych operacji
* <!-- .element: class="fragment fade-in" --> może być niebezpieczne w aplikacjach wielowątkowych (jak każde przekazywanie przez <code>&</code>)

___

### Używaj referencji zamiast wskaźników

* <!-- .element: class="fragment fade-in" --> Jaka jest różnica pomiędzy wskaźnikiem i referencją?
  * <!-- .element: class="fragment fade-in" --> referencja nie może być pusta
  * <!-- .element: class="fragment fade-in" --> nie można zmienić przypisania referencji, aby wskazywała na inny obiekt
* <!-- .element: class="fragment fade-in" --> Priorytety użycia (jeśli możliwe):
  * <!-- .element: class="fragment fade-in" --> <code>(const) T&</code>
  * <!-- .element: class="fragment fade-in" --> <code>std::unique_ptr&ltT&gt</code>
  * <!-- .element: class="fragment fade-in" --> <code>std::shared_ptr&ltT&gt</code>
  * <!-- .element: class="fragment fade-in" --> <code>T*</code>

___
<!-- .slide: style="font-size: 0.9em" -->
## Zadanie: `List`

Zajrzyj do pliku `List.cpp`, w którym jest zaimplementowana prosta (i niepoprawna) lista (single-linked list).

* `void add(Node* node)` dodaje nowy element `Node` na końcu listy
* `Node* get(const int value)` iteruje po liście i zwraca pierwszy element, którego wartość wynosi `value` lub `nullptr`

1. <!-- .element: class="fragment fade-in" --> Skompiluj i uruchom aplikację List
2. <!-- .element: class="fragment fade-in" --> Napraw wycieki pamięci bez stosowania smart pointerów
3. <!-- .element: class="fragment fade-in" --> Napraw wycieki pamięci stosując smart pointery. Jaki ich rodzaj zastosujesz i dlaczego?
4. <!-- .element: class="fragment fade-in" --> (Opcjonalnie) Co się stanie jeśli na listę dodamy ten sam element 2 razy? Napraw problem.
5. <!-- .element: class="fragment fade-in" --> (Opcjonalnie) Utwórz wyjątek <code>EmptyListError</code> (dziedziczący po <code>std::runtime_error</code>). Dodaj jego rzucanie i łapanie we właściwych miejscach.
