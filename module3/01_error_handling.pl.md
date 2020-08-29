<!-- .slide: data-background="#111111" -->

# Error handling methods

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

## Error codes

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

### Error handling in constructors and operators

Constructors and operators have strictly defined return types (or no return type). It is impossible to return a custom error code from them.

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

Instead of returning a special value from a function or setting an error code we just `throw` an exception. It indicates that something went wrong and we can handle this case in another place.

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

`try` block is a place where we can expect an exception. `catch` blocks tries to match the exception type.

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

## What is an exception?

Every object can work as an exception.
<!-- .element: class="fragment fade-in" -->

```cpp
throw 42;
```
<!-- .element: class="fragment fade-in" -->

However, it's not recommended to use build-in types or any user created classes as an exception.
<!-- .element: class="fragment fade-in" -->

```cpp
throw std::runtime_error{"Huston, we have a problem"};
```
<!-- .element: class="fragment fade-in" -->

It is recommended to use exceptions from the standard library (like `std::runtime_error`) of create own exception classes that inherits from `std::exception`.
<!-- .element: class="fragment fade-in" -->
