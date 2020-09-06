<!-- .slide: data-background="#111111" -->

# Najlepsze praktyki

___

## Najlepsze praktyki

* <!-- .element: class="fragment fade-in" --> Zasada 0, Zasada 5
* <!-- .element: class="fragment fade-in" --> Unikaj jawnego <code>new</code>
* <!-- .element: class="fragment fade-in" --> Używaj <code>std::make_shared()</code> / <code>std::make_unique()</code>
* <!-- .element: class="fragment fade-in" --> Kopiowanie <code>std::shared_ptr<></code>
* <!-- .element: class="fragment fade-in" --> Używaj odwołań zamiast wskaźników

___

## Zasada 0, Zasada 5

### Zasada 5 <!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Jeśli potrzebujesz zaimplementować jedną z tych funkcji:
  * <!-- .element: class="fragment fade-in" --> destruktor
  * <!-- .element: class="fragment fade-in" --> konstruktor kopiujący
  * <!-- .element: class="fragment fade-in" --> operator przypisania kopii
  * <!-- .element: class="fragment fade-in" --> konstruktor przenoszący
  * <!-- .element: class="fragment fade-in" --> operator przypisania przeniesienia
* <!-- .element: class="fragment fade-in" --> Prawdopodobnie oznacza to, że powinieneś wdrożyć je wszystkie, ponieważ masz ręczne zarządzanie zasobami.

### Zasada 0 <!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Jeśli używasz ramek RAII na zasobach, nie musisz implementować żadnej z funkcji reguły 5.

___

## Unikaj jawnych `new`

* <!-- .element: class="fragment fade-in" --> Inteligentne wskaźniki eliminują potrzebę jawnego używania funkcji <code>delete</code>
* <!-- .element: class="fragment fade-in" --> Aby zachować symetrię, nie używaj również <code>new</code>
* <!-- .element: class="fragment fade-in" --> Przydziel za pomocą:
  * <!-- .element: class="fragment fade-in" --> <code>std::make_unique()</code>
  * <!-- .element: class="fragment fade-in" --> <code>std::make_shared()</code>

___

<!-- .slide: style="font-size: 0.8em" -->

### Używaj `std::make_shared()` / `std::make_unique()`

* <!-- .element: class="fragment fade-in" --> Jaki jest tu problem?

```cpp
struct MyData { int value; };
using Ptr = std::shared_ptr<MyData>;
void sink(Ptr oldData, Ptr newData);

void use(void) {
    sink(Ptr{new MyData{41}}, Ptr{new MyData{42}});
}
```
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Wskazówka: ta wersja nie jest problematyczna

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

### Dekonstrukcja alokacji

`auto p = new MyData(10);` oznacza:

* <!-- .element: class="fragment fade-in" --> przydziel <code>sizeof(MyData)</code> bajtów
* <!-- .element: class="fragment fade-in" --> uruchom konstruktor <code>MyData</code>
* <!-- .element: class="fragment fade-in" --> przypisz adres przydzielonej pamięci do <code>p</code>

Kolejność oceny operandów prawie wszystkich operatorów C++ (w tym kolejność oceny argumentów funkcji w wyrażeniu  wywołania funkcji i kolejność oceny podwyrażenia w dowolnym wyrażeniu) jest **nieokreślona**.

<!-- .element: class="fragment fade-in box" -->

___
<!-- .slide: style="font-size: 0.77em" -->

### Nieokreślona kolejność oceniania

* Co powiesz o takich dwóch operacjach?

| pierwsza operacja (A)                          | druga operacja (B)                              |
| :--------------------------------------------- | :---------------------------------------------- |
| (1) alokuj `sizeof(MyData)` bitów              | (1) alokuj `sizeof(MyData)` bitów               |
| (2) uruchom konstruktor `MyData`               | (2) uruchom konstruktor `MyData`                |
| (3) przypisz adres przydzielonej pamięci do `p`| (3) przypisz adres przydzielonej pamięci do `p` |

* <!-- .element: class="fragment fade-in" --> Nieokreślona kolejność wyceny oznacza, że przykładowa kolejność może być następująca:
  * A1, A2, B1, B2, C3, C3
* <!-- .element: class="fragment fade-in" --> Co jeśli B2 zgłosi wyjątek?

___

### Używaj `std::make_shared()` / `std::make_unique()`

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

* <!-- .element: class="fragment fade-in" --> Naprawia poprzedni błąd
* <!-- .element: class="fragment fade-in" --> Nie powtarza skonstruowanego typu
* <!-- .element: class="fragment fade-in" --> Nie używa jawnego <code>new</code>
* <!-- .element: class="fragment fade-in" --> Optymalizuje użycie pamięci (tylko dla <code>std::make_shared()</code>)

___

## Kopiowanie `std::shared_ptr<>`

```cpp
void foo(std::shared_ptr<MyData> p);

void bar(std::shared_ptr<MyData> p) {
    foo(p);
}
```

* <!-- .element: class="fragment fade-in" --> wymaga inkrementacji / dekrementacji liczników
* <!-- .element: class="fragment fade-in" --> zmienne atomowe / blokady nie są darmowe
* <!-- .element: class="fragment fade-in" --> wywoła destruktory

##### Może być lepiej?
<!-- .element: class="fragment fade-in" -->

___

## Kopiowanie `std::shared_ptr<>`

```cpp
void foo(const std::shared_ptr<MyData> & p);

void bar(const std::shared_ptr<MyData> & p) {
    foo(p);
}
```

* <!-- .element: class="fragment fade-in" --> tak szybko, jak przekazanie wskaźnika
* <!-- .element: class="fragment fade-in" --> bez dodatkowych operacji
* <!-- .element: class="fragment fade-in" --> nie jest bezpieczny w aplikacjach wielowątkowych

___

### Używaj odwołań zamiast wskaźników

* <!-- .element: class="fragment fade-in" --> Jaka jest różnica między wskaźnikiem a referencją?
  * <!-- .element: class="fragment fade-in" --> odniesienie nie może być puste
  * <!-- .element: class="fragment fade-in" --> odniesienie, po przypisaniu, nie może wskazywać na nic innego
* <!-- .element: class="fragment fade-in" --> Priorytety użytkowania (jeśli to możliwe):
  * <!-- .element: class="fragment fade-in" --> <code>(const) T&</code>
  * <!-- .element: class="fragment fade-in" --> <code>std::unique_ptr&ltT&gt</code>
  * <!-- .element: class="fragment fade-in" --> <code>std::shared_ptr&ltT&gt</code>
  * <!-- .element: class="fragment fade-in" --> <code>T*</code>

___

## Ćwiczenie: List

Spójrz na plik `List.cpp`, w którym zaimplementowano prostą (i błędną) listę jednokierunkową.

* Metoda `void add(Node* node)` dodaje nowy węzeł na końcu listy.
* Metoda `Node* get(const int value)` iteruje po liście i zwraca pierwszy węzeł z pasującym argumentem `value` lub `nullptr`

1. <!-- .element: class="fragment fade-in" --> Skompiluj i uruchom aplikację List
2. <!-- .element: class="fragment fade-in" --> Napraw wycieki pamięci bez wprowadzania inteligentnych wskaźników
3. <!-- .element: class="fragment fade-in" --> Napraw wycieki pamięci za pomocą inteligentnych wskaźników. Jakie wskaźniki należy zastosować i dlaczego?
4. <!-- .element: class="fragment fade-in" --> (Opcjonalnie) Co się stanie, gdy ten sam węzeł zostanie dodany dwukrotnie? Rozwiąż ten problem.
5. <!-- .element: class="fragment fade-in" --> (Opcjonalnie) Utwórz wyjątek <code>EmptyListError</code> (pochodzący z <code>std::runtime_error</code>). Dodaj rzucanie i łapanie w odpowiednich miejscach.
