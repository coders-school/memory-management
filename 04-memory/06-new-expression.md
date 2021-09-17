## Wyrażenie `new` i operator `new`

[wyrażenie `new`](https://en.cppreference.com/w/cpp/language/new) robi 3 rzeczy:

* <!-- .element: class="fragment fade-in" --> alokuje <code>sizeof(T)</code> bajtów na stercie (za pomocą <a href="https://en.cppreference.com/w/cpp/memory/new/operator_new">operatora <code>new</code></a>)
* <!-- .element: class="fragment fade-in" --> wywołuje konstruktor <code>T</code> na zaalokowanej pamięci
* <!-- .element: class="fragment fade-in" --> przypisuje adres do wskaźnika

```cpp
// replaceable allocation functions
void* operator new ( std::size_t count );
void* operator new[]( std::size_t count );
// replaceable non-throwing allocation functions
void* operator new ( std::size_t count, const std::nothrow_t& tag);
void* operator new[]( std::size_t count, const std::nothrow_t& tag);
// user-defined placement allocation functions
void* operator new ( std::size_t count, user-defined-args... );
void* operator new[]( std::size_t count, user-defined-args... );
// additional param std::align_val_t since C++17, [[nodiscard]] since C++20
// some more versions on https://en.cppreference.com/w/cpp/memory/new/operator_new
```
<!-- .element: class="fragment fade-in" -->
