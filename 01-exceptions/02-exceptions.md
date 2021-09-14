<!-- .slide: data-background="#111111" -->

# Jak to działa?

___
<!-- .slide: style="font-size: 0.9em" -->

## Dopasowanie typu wyjątku

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

### Wynik

`Constructor` <!-- .element: class="fragment fade-in" -->

`Constructor` <!-- .element: class="fragment fade-in" -->

`Destructor` <!-- .element: class="fragment fade-in" -->

`runtime_error: Error` <!-- .element: class="fragment fade-in" -->

`Destructor` <!-- .element: class="fragment fade-in" -->

</div>
</div>

___

## Mechanizm odwijania stosu

* <!-- .element: class="fragment fade-in" --> Rzucony wyjątek startuje mechanizm odwijania stosu (stack unwinding mechanism)
* <!-- .element: class="fragment fade-in" --> Typ wyjątku jest dopasowywany do kolejnych klauzul <code>catch</code>
* <!-- .element: class="fragment fade-in" --> Wyjątek jest polimorficzny, tzn. może zostać dopasowany do typu klasy bazowej
* <!-- .element: class="fragment fade-in" --> Jeśli typ pasuje:
  * <!-- .element: class="fragment fade-in" --> Wszystko zaalokowane na stosie jest niszczone w odwrotnej kolejności aż do napotkania bloku <code>try</code>
  * <!-- .element: class="fragment fade-in" --> Kod z pasującej klauzuli <code>catch</code> jest wykonywany
  * <!-- .element: class="fragment fade-in" --> Obiekt wyjątku jest niszczony
* <!-- .element: class="fragment fade-in" --> Jeśli typ nie pasuje do żadnej klauzuli <code>catch</code>, odwijanie stosu jest kontynuowane do kolejnego bloku <code>try</code>

___
<!-- .slide: style="font-size: 0.9em" -->

## Nieobsłużony wyjątek

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

### Wynik

`Constructor` <!-- .element: class="fragment fade-in" -->

`Constructor` <!-- .element: class="fragment fade-in" -->

`>> abort() <<` <!-- .element: class="fragment fade-in" -->

</div>
</div>

___

## Czemu destruktory nie zostały wywołane?

* <!-- .element: class="fragment fade-in" --> Mechanizm odwijania stosu najpierw sprawdza, czy w obecnym bloku <code>try</code> jest pasująca klauzula <code>catch</code> jeszcze przed zniszczeniem obiektów
* <!-- .element: class="fragment fade-in" --> Wyjątek który nie został przechwycony i wypada po funkcję main powoduje zawołanie <code>std::terminate()</code>, które ubija program.

___
<!-- .slide: style="font-size: 0.9em" -->

## Ponowne rzucanie wyjątków

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

Samo `throw` w bloku `catch` powoduje ponowne rzucenie aktualnego wyjątku.

### Wynik <!-- .element: class="fragment fade-in" -->

`Constructor` <!-- .element: class="fragment fade-in" -->

`Constructor` <!-- .element: class="fragment fade-in" -->

`Destructor` <!-- .element: class="fragment fade-in" -->

`exception` <!-- .element: class="fragment fade-in" -->

`runtime_error: Error` <!-- .element: class="fragment fade-in" -->

`Destructor` <!-- .element: class="fragment fade-in" -->

</div>
</div>

___

## Ponowne rzucanie wyjątku

* <!-- .element: class="fragment fade-in" --> Wyjątek rzucony ponownie raz jeszcze uruchamia mechanizm odwijania stosu
* <!-- .element: class="fragment fade-in" --> Odwijanie stosu jest kontynuowane do kolejnego bloku <code>try</code>
* <!-- .element: class="fragment fade-in" --> Klauzula <code>catch</code> dla typu bazowego przechwyci też wyjątki typów pochodnych
* <!-- .element: class="fragment fade-in" --> Ponowne rzucenie wyjątki nie zmienia oryginalnego typu wyjątku

___
<!-- .slide: style="font-size: 0.9em" -->

## Rzucenie wyjątku podczas odwijania stosu

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

### Wynik

`Constructor` <!-- .element: class="fragment fade-in" -->

`Throwing c-tor` <!-- .element: class="fragment fade-in" -->

`>> abort() <<`  <!-- .element: class="fragment fade-in" -->

</div>
</div>

___

## Wnioski

* <!-- .element: class="fragment fade-in" --> Można obsługiwać tylko jeden wyjątek na raz
* <!-- .element: class="fragment fade-in" --> Wyjątek rzucony podczas odwijania stosu powoduje ubicie programu - woła się <code>std::terminate()</code>
* <!-- .element: class="fragment fade-in" --> Nigdy nie rzucaj wyjątków w destruktorach
