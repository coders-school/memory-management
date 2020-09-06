<!-- .slide: data-background="#111111" -->

## Zależności cykliczne

<img data-src="img/cyclicinverted.png" alt="cyclic dependencies" class="plain fragment fade-in">

* <!-- .element: class="fragment fade-in" --> Zależność cykliczna występuje wtedy, gdy masz klasę A z elementem odwołującym się do siebie.
* <!-- .element: class="fragment fade-in" --> Zależność cykliczna występuje wtedy, gdy masz dwie klasy A i B, gdzie A ma odniesienie do B, które ma odniesienie do A.
* <!-- .element: class="fragment fade-in" --> Jak to naprawić?

___

### `std::weak_ptr<>` na ratunek

#### Cechy

* <!-- .element: class="fragment fade-in" --> nie jest właścicielem obiektu
* <!-- .element: class="fragment fade-in" --> tylko obserwuje
* <!-- .element: class="fragment fade-in" --> należy przekonwertować na <code>std::shared_ptr<></code>, aby uzyskać dostęp do obiektu
* <!-- .element: class="fragment fade-in" --> można utworzyć tylko na podstawie <code>std::shared_ptr<></code>

<div>
    <img data-src="img/weakptrinverted.png" alt="weak pointers" class="plain fragment fade-in">
</div>

___

### użycie `std::weak_ptr<>`

<div class="multicolumn" style="position: relative">
<div class="col" style="width: 65%; flex: none">

```cpp
#include <memory>
#include <iostream>

struct Msg { int value; };

void checkMe(const std::weak_ptr<Msg> & wp) {
    std::shared_ptr<Msg> p = wp.lock();
    if (p)
        std::cout << p->value << '\n';
    else
        std::cout << "Expired\n";
}

int main() {
    auto sp = std::shared_ptr<Msg>{new Msg{10}};
    auto wp = std::weak_ptr<Msg>{sp};
    checkMe(wp);
    sp.reset();
    checkMe(wp);
}
```

</div>

<div class="col fragment fade-in">

```bash
> ./a.out
10
Expired
```

</div>
</div>

___

### Zależności cykliczne `std::shared_ptr<>`

* Jak rozwiązać ten problem?

```cpp
#include <memory>

struct Node {
    std::shared_ptr<Node> child;
    std::shared_ptr<Node> parent;
};

int main () {
    auto root = std::shared_ptr<Node>(new Node);
    auto child = std::shared_ptr<Node>(new Node);
    root->child = child;
    child->parent = root;
}
```

___

### Złamanie cyklu - rozwiązanie

* Użyj `std::week_ptr<Node>` w jednym kierunku

```cpp
#include <memory>
struct Node {
    std::shared_ptr<Node> child;
    std::weak_ptr<Node> parent;
};

int main () {
    auto root = std::shared_ptr<Node>(new Node);
    auto child = std::shared_ptr<Node>(new Node);
    root->child = child;
    child->parent = root;
}
```

```text
==148== All heap blocks were freed -- no leaks are possible
```
<!-- .element: class="fragment fade-in" -->
