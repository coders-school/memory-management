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

## Kody błędów

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

Konstruktory i operatory mają ściśle zdefiniowane typy zwracane (lub brak typu zwracanego). Niemożliwe jest zwrócenie od nich niestandardowego kodu błędu.

```cpp
struct FileWrapper {
    FileWrapper(std::string const& filePath)
            : m_file(fopen(filePath.c_str(), "rw")) {
        /* A jeśli plik się nie otworzył? */
    }

    ~FileWrapper() {
        fclose(m_file);
    }

    FileWrapper & operator<<(std::string const& text) {
        /* A jeśli plik się nie otworzył? */
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

Zamiast zwracać specjalną wartość z funkcji lub ustawiać kod błędu, po prostu `throw`(rzucamy) wyjątek. Wskazuje, że coś poszło nie tak i możemy zająć się tą sprawą w innym miejscu.

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
        /* Nie jest wymagana weryfikacja, nie można utworzyć nieprawidłowego obiektu */
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

Blok `try` to miejsce, w którym możemy spodziewać się wyjątku. Bloki `catch` próbują dopasować typ wyjątku.

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

### Rezultat

`std::runtime_error`

</div>
</div>

___

## Czym jest wyjątek?

Każdy obiekt może działać jako wyjątek.
<!-- .element: class="fragment fade-in" -->

```cpp
throw 42;
```
<!-- .element: class="fragment fade-in" -->

Jednak nie zaleca się używania typów wbudowanych ani klas utworzonych przez użytkownika jako wyjątków.
<!-- .element: class="fragment fade-in" -->

```cpp
throw std::runtime_error{"Huston, we have a problem"};
```
<!-- .element: class="fragment fade-in" -->

Zaleca się używanie wyjątków ze standardowej biblioteki (np. `std::runtime_error`) lub tworzenie własnych klas wyjątków, dziedziczących po `std::exception`.
<!-- .element: class="fragment fade-in" -->
