## Alokacja stosu

<div class="multicolumn">
<div class="col">

* <!-- .element: class="fragment fade-in" --> Stos wywołań składa się z ramek stosu

* <!-- .element: class="fragment fade-in" --> Ramka stosu zwykle zawiera co najmniej:
  * <!-- .element: class="fragment fade-in" --> argumenty przekazane do funkcji (jeśli istnieją)
  * <!-- .element: class="fragment fade-in" --> adres zwrotny do wywołania
  * <!-- .element: class="fragment fade-in" --> miejsce na zmienne lokalne (jeśli istnieją)
* <!-- .element: class="fragment fade-in" --> Automatyczne cofanie przydziału, gdy poza zakresem

<img height="200" data-src="img/stack.png" src="img/stack.png" alt="stack" class="plain">
<!-- .element: class="fragment fade-in" -->

</div>
<div class="col">

```cpp
#include <iostream>

int sum(int a, int b)
{
    return a + b;
}

int main()
{
    int a = 10;
    int b = 20;

    std::cout << sum(a, b);

    return 0;
}


```

</div>
</div>