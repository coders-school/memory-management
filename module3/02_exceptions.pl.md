<!-- .slide: data-background="#111111" -->

# How does it work?

___
<!-- .slide: style="font-size: 0.9em" -->

## Matching exceptions

<div class="multicolumn" style="position: relative">
<div class="col" style="width: 75%; flex: none">

```cpp
struct TalkingObject {
    TalkingObject()  { cout << "Constructor" << '\n'; }
    ~TalkingObject() { cout << "Destructor" << '\n'; }
};

void foo() { throw std::runtime_error("Error"); }

int main() {
    TalkingObject outside;
    try {
        TalkingObject inside;
        foo();
    } catch(runtime_error const& ex) {
        cout << "runtime_error: " << ex.what() << '\n';
    } catch(exception const&) {
        cout << "exception" << '\n';
    }
}
```

</div>
<div class="col fragment fade-in">

### Result

`Constructor` <!-- .element: class="fragment fade-in" -->

`Constructor` <!-- .element: class="fragment fade-in" -->

`Destructor` <!-- .element: class="fragment fade-in" -->

`runtime_error: Error` <!-- .element: class="fragment fade-in" -->

`Destructor` <!-- .element: class="fragment fade-in" -->

</div>
</div>

___

## Stack unwinding mechanism

* <!-- .element: class="fragment fade-in" --> Thrown exceptions starts a stack unwinding mechanism
* <!-- .element: class="fragment fade-in" --> The exception type is being matched with consecutive <code>catch</code> clauses
* <!-- .element: class="fragment fade-in" --> If the exception type is matched:
  * <!-- .element: class="fragment fade-in" --> Everything allocated on stack is destroyed in a reversed order until reaching <code>try</code> block
  * <!-- .element: class="fragment fade-in" --> The code from matching <code>catch</code> clause is executed
  * <!-- .element: class="fragment fade-in" --> The exception object is destroyed
* <!-- .element: class="fragment fade-in" --> If the exception type is not matched with any <code>catch</code> clause, the stack unwinding continues to the next <code>try</code> block

___
<!-- .slide: style="font-size: 0.9em" -->

## Unhandled exception

<div class="multicolumn" style="position: relative">
<div class="col" style="width: 75%; flex: none">

```cpp
struct TalkingObject { /*...*/ };

void foo() { throw std::runtime_error("Error"); }

void bar() {
    try {
        TalkingObject inside;
        foo();
    } catch(std::logic_error const&) {
        std::cout << "std::logic_error" << '\n';
    }
}

int main() {
    TalkingObject outside;
    bar();
}
```

</div>
<div class="col fragment fade-in">

### Result

`Constructor` <!-- .element: class="fragment fade-in" -->

`Constructor` <!-- .element: class="fragment fade-in" -->

`>> abort() <<` <!-- .element: class="fragment fade-in" -->

</div>
</div>

___

## Why destructors have not been called?

* <!-- .element: class="fragment fade-in" --> The stack unwinding mechanism first check for a matching <code>catch</code> clause in a current <code>try</code> block before destroying objects
* <!-- .element: class="fragment fade-in" --> An exception which was not caught and falls out of the main function scope calls <code>std::terminate()</code>. It kills the program.

___
<!-- .slide: style="font-size: 0.9em" -->

## Exception rethrowing

<div class="multicolumn" style="position: relative">
<div class="col" style="width: 75%; flex: none">

```cpp
struct TalkingObject { /*...*/ };

void foo() { throw std::runtime_error("Error"); }

void bar() try {
    TalkingObject inside;
    foo();
} catch(std::exception const&) {
    std::cout << "exception" << '\n';
    throw;
}

int main() {
    TalkingObject outside;
    try {
        bar();
    } catch(std::runtime_error const& ex) {
        std::cout << "runtime_error: " << ex.what() << '\n';
    }
}
```

</div>
<div class="col fragment fade-in">

Bare `throw` in a `catch` clause rethrows a current exception.

### Result <!-- .element: class="fragment fade-in" -->

`Constructor` <!-- .element: class="fragment fade-in" -->

`Constructor` <!-- .element: class="fragment fade-in" -->

`Destructor` <!-- .element: class="fragment fade-in" -->

`exception` <!-- .element: class="fragment fade-in" -->

`runtime_error: Error` <!-- .element: class="fragment fade-in" -->

`Destructor` <!-- .element: class="fragment fade-in" -->

</div>
</div>

___

## Exception rethrowing

* <!-- .element: class="fragment fade-in" --> Rethrown exception starts a stack unwinding once again
* <!-- .element: class="fragment fade-in" --> Stack unwinding continues until another <code>try</code> block is reached
* <!-- .element: class="fragment fade-in" --> <code>catch</code> clause for a base type can catch an exception of a derived type
* <!-- .element: class="fragment fade-in" --> It does not change the original exception type, when it is rethrown

___
<!-- .slide: style="font-size: 0.9em" -->

## Throwing an exception during stack unwinding

<div class="multicolumn" style="position: relative">
<div class="col" style="width: 75%; flex: none">

```cpp
struct TalkingObject { /*...*/ };
struct ThrowingObject {
    ThrowingObject() { std::cout << "Throwing c-tor\n"; }
    ~ThrowingObject() {
        throw std::runtime_error("error in destructor");
    }
};

void foo() { throw std::runtime_error("Error"); }

int main() {
    TalkingObject outside;
    try {
        ThrowingObject inside;
        foo();
    } catch(std::exception const&) {
        std::cout << "std::exception" << '\n';
        throw;
    }
}
```

</div>
<div class="col fragment fade-in">

### Result

`Constructor` <!-- .element: class="fragment fade-in" -->

`Throwing c-tor` <!-- .element: class="fragment fade-in" -->

`>> abort() <<`  <!-- .element: class="fragment fade-in" -->

</div>
</div>

___

## Conclusions

* <!-- .element: class="fragment fade-in" --> Only one exception can be handled at a time
* <!-- .element: class="fragment fade-in" --> The exception thrown during stack unwinding causes termination of the program - <code>std::terminate()</code> is called
* <!-- .element: class="fragment fade-in" --> You should never throw an exception in a destructor
