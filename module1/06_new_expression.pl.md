## Wyrażenie `new` i `operator new`

[Wyrażenie new](https://en.cppreference.com/w/cpp/language/new) robi 3 rzeczy:

* <!-- .element: class="fragment fade-in" --> alokacja <code>sizeof(T)</code> bajtów na stercie (poprzez odpowiedni <a href="https://en.cppreference.com/w/cpp/memory/new/operator_new">operator <code>new</code></a>)
* <!-- .element: class="fragment fade-in" --> wywołanie konstruktora <code>T</code> na przydzielonej pamięci
* <!-- .element: class="fragment fade-in" --> przypisanie adresu pamięci do wskaźnika

```cpp
// wymienne funkcje alokacji
void* operator new ( std::size_t count );
void* operator new[]( std::size_t count );
// wymienne, nierzucające funkcje alokacji
void* operator new ( std::size_t count, const std::nothrow_t& tag);
void* operator new[]( std::size_t count, const std::nothrow_t& tag);
// definiowane przez użytkownika funkcje alokacji miejsc docelowych
void* operator new ( std::size_t count, user-defined-args... );
void* operator new[]( std::size_t count, user-defined-args... );
// dodatkowy parametr std::align_val_t od C++17, [[nodiscard]] od C++20
// kilka innych wersji na https://en.cppreference.com/w/cpp/memory/new/operator_new
```
<!-- .element: class="fragment fade-in" -->
