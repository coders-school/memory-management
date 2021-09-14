<!-- .slide: data-background="#111111" -->

# Metody obsługi błędów

___

## `goto`

```cpp
#include <iostream>

bool isValid() { /* ... */ }

int main() {
    // ...
    if(!isValid()) {
        goto error;
    }

error:
    std::cerr << "Error occured" << '\n';
    return 1;
}
```

___

## `errno`

W programowaniu w C/C++ jest też koncepcja `errno`, czyli statycznej współdzielonej zmiennej, którą ustawia się na odpowiednią wartość w przypadku wystąpienia błędu. Zobacz [`errno` na cppreference](https://en.cppreference.com/w/cpp/error/errno).

```cpp
int main() {
    double not_a_number = std::log(-1.0);
    std::cout << not_a_number << '\n';
    if (errno == EDOM) {
        std::cout << "log(-1) failed: " << std::strerror(errno) << '\n';
        std::setlocale(LC_MESSAGES, "de_DE.utf8");
        std::cout << "Or, in German, " << std::strerror(errno) << '\n';
    }
}
```

___

## Kody powrotu / kody błędów

```cpp
#include <iostream>

enum class ErrorCode { Ok, FailCause1, FailCause2 };
bool isValid() { /* ... */ }

ErrorCode foo() {
    if(!isValid()) {
        return ErrorCode::FailCause1;
    }
    // ...
    return ErrorCode::Ok;
}

int main() {
    if(foo() == ErrorCode::FailCause1) {
        std::cerr << "Error occured" << '\n';
        return 1;
    }
    return 0;
}
```

___
<!-- .slide: style="font-size: 0.9em" -->

### Obsługa błędów w konstruktorach i operatorach

Konstruktory i operatory mają ściśle zdefiniowane typy zwracane (lub ich brak). Niemożliwe jest zwrócenie w nich własnego kodu powrotu.

```cpp
struct FileWrapper {
    FileWrapper(std::string const& filePath)
            : m_file(fopen(filePath.c_str(), "rw")) {
        /* What if the file did not open? */
    }

    ~FileWrapper() {
        fclose(m_file);
    }

    FileWrapper & operator<<(std::string const& text) {
        /* What if the file did not open? */
        fputs(text.c_str(), m_file);
        return *this;
    }

private:
    FILE* m_file;
};
```

___
<!-- .slide: style="font-size: 0.85em" -->

## `throw`

Zamiast zwracać specjalną wartość z funkcji lub ustawiać globalną zmienną po prostu rzucamy wyjątkiem. To wskazuje, że coś poszło nie tak, a błąd możemy obsłużyć w zupełnie innym miejscu.

```cpp
struct FileWrapper {
    FileWrapper(std::string const& filePath)
            : m_file(fopen(filePath.c_str(), "rw")) {
        if(!m_file) {
            throw std::runtime_error("File not opened");
        }
    }

    ~FileWrapper() {
        fclose(m_file);
    }

    FileWrapper & operator<<(std::string const& text) {
        /* Not validation needed, invalid object cannot be created */
        fputs(text.c_str(), m_file);
        return *this;
    }

private:
    FILE* m_file;
};
```

___
<!-- .slide: style="font-size: 0.85em" -->

## `try/catch`

Za pomocą `try` oznaczamy blok kodu, w którym możliwe jest rzucenie wyjątku. Bloki `catch` służą do łapania wyjątków określonych typów.

<div class="multicolumn" style="position: relative">
<div class="col" style="width: 75%; flex: none">

```cpp
#include <iostream>
#include <stdexcept>

void foo() { throw std::runtime_error("Error"); }

int main() {
    try {
        foo();
    } catch(std::runtime_error const&) {
        std::cout << "std::runtime_error" << std::endl;
    } catch(std::exception const& ex) {
        std::cout << "std::exception: " << ex.what() << std::endl;
    } catch(...) {
        std::cerr << "unknown exception" << std::endl;
    }
}
```

</div>
<div class="col fragment fade-in">

### Result

`std::runtime_error`

</div>
</div>

___

## Co to jest wyjątek?

W ogólności - dowolny obiekt. Każdy obiekt może być wyjątkiem.
<!-- .element: class="fragment fade-in" -->

```cpp
throw 42;
```
<!-- .element: class="fragment fade-in" -->

Nie jest rekomendowane używanie wbudowanych typów lub tworzonych klas jako wyjątki.
<!-- .element: class="fragment fade-in" -->

```cpp
throw std::runtime_error{"Huston, we have a problem"};
```
<!-- .element: class="fragment fade-in" -->

Poleca się, aby wyjątki były specjalnymi klasami, które dziedziczą po innych klasach wyjątków z biblioteki standardowej. Przykładem może być `std::runtime_error`, który dziedziczy po `std::exception`.
<!-- .element: class="fragment fade-in" -->
