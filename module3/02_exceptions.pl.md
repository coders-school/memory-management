<!-- .slide: data-background="#111111" -->

# Jak to działa?

___
<!-- .slide: style="font-size: 0.9em" -->

## Pasujące wyjątki

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

### Rezultat

`Constructor` <!-- .element: class="fragment fade-in" -->

`Constructor` <!-- .element: class="fragment fade-in" -->

`Destructor` <!-- .element: class="fragment fade-in" -->

`runtime_error: Error` <!-- .element: class="fragment fade-in" -->

`Destructor` <!-- .element: class="fragment fade-in" -->

</div>
</div>

___

## Mechanizm odwijania stosu

* <!-- .element: class="fragment fade-in" --> Zgłoszone wyjątki uruchamiają mechanizm rozwijania stosu
* <!-- .element: class="fragment fade-in" --> Typ wyjątku jest dopasowywany do kolejnych klauzul <code>catch</code>
* <!-- .element: class="fragment fade-in" --> Jeśli typ wyjątku jest dopasowany:
  * <!-- .element: class="fragment fade-in" --> Wszystko przydzielone na stosie jest niszczone w odwrotnej kolejności, aż do osiągnięcia bloku <code>try</code>
  * <!-- .element: class="fragment fade-in" --> Wykonywany jest kod z pasującej klauzuli <code>catch</code>
  * <!-- .element: class="fragment fade-in" --> Obiekt wyjątku zostaje zniszczony
* <!-- .element: class="fragment fade-in" --> Jeśli typ wyjątku nie jest dopasowany do żadnej klauzuli <code>catch</code>, rozwijanie stosu jest kontynuowane do następnego bloku <code>try</code>

___
<!-- .slide: style="font-size: 0.9em" -->

## Nieobsługiwany wyjątek

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

### Rezultat

`Constructor` <!-- .element: class="fragment fade-in" -->

`Constructor` <!-- .element: class="fragment fade-in" -->

`>> abort() <<` <!-- .element: class="fragment fade-in" -->

</div>
</div>

___

## Dlaczego nie wywołano destruktorów?

* <!-- .element: class="fragment fade-in" --> Mechanizm rozwijania stosu najpierw sprawdza pasującą klauzulę <code>catch</code> w bieżącym bloku <code>try</code> przed zniszczeniem obiektów
* <!-- .element: class="fragment fade-in" --> Wyjątek, który nie został przechwycony i wypada z głównego zakresu funkcji wywołuje <code>std::terminate()</code>. To zabija program.

___
<!-- .slide: style="font-size: 0.9em" -->

## Ponowne zgłoszenie wyjątku

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

Samo `throw` w klauzuli `catch` ponownie zgłasza bieżący wyjątek.

### Rezultat <!-- .element: class="fragment fade-in" -->

`Constructor` <!-- .element: class="fragment fade-in" -->

`Constructor` <!-- .element: class="fragment fade-in" -->

`Destructor` <!-- .element: class="fragment fade-in" -->

`exception` <!-- .element: class="fragment fade-in" -->

`runtime_error: Error` <!-- .element: class="fragment fade-in" -->

`Destructor` <!-- .element: class="fragment fade-in" -->

</div>
</div>

___

## Ponowne zgłoszenie wyjątku

* <!-- .element: class="fragment fade-in" --> Ponownie zgłoszony wyjątek uruchamia ponownie rozwijanie stosu
* <!-- .element: class="fragment fade-in" --> Odwijanie stosu trwa aż do osiągnięcia kolejnego bloku <code>try</code>
* <!-- .element: class="fragment fade-in" --> Klauzula <code>catch</code> dla typu podstawowego może przechwycić wyjątek typu pochodnego
* <!-- .element: class="fragment fade-in" --> Nie zmienia oryginalnego typu wyjątku, gdy jest ponownie generowany

___
<!-- .slide: style="font-size: 0.9em" -->

## Zgłaszanie wyjątku podczas rozwijania stosu

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

### Rezultat

`Constructor` <!-- .element: class="fragment fade-in" -->

`Throwing c-tor` <!-- .element: class="fragment fade-in" -->

`>> abort() <<`  <!-- .element: class="fragment fade-in" -->

</div>
</div>

___

## Konkluzja

* <!-- .element: class="fragment fade-in" --> Jednocześnie można obsłużyć tylko jeden wyjątek
* <!-- .element: class="fragment fade-in" --> Wyjątek zgłoszony podczas rozwijania stosu powoduje zakończenie działania programu - wywoływana jest funkcja <code>std::terminate()</code>
* <!-- .element: class="fragment fade-in" --> Nigdy nie należy zgłaszać wyjątku w destruktorze
