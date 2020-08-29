## Alokacja sterty

<div class="multicolumn">
<div class="col" style="margin-top: 70px; font-size: 85%;">

Alokacja sterty składa się z kilku kroków:
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> alokacja wskaźnika na stosie
* <!-- .element: class="fragment fade-in" --> alokacja <code>sizeof(T)</code> bajtów na stercie
* <!-- .element: class="fragment fade-in" --> wywołanie konstruktora <code>T</code> na przydzieloną pamięć
* <!-- .element: class="fragment fade-in" --> przypisanie adresu pamięci do wskaźnika
* <!-- .element: class="fragment fade-in" --> ręczne cofnięcie przydziału przy użyciu operatora <code>delete</code>

</div>
<div class="col" style="margin: 15px;">

```cpp
void heap()
{
    int *p = new int(100);
    delete p;
}

void heap()
{
    int *p;
    p = (int*)malloc(sizeof(int));
    *p = 100;
    free(p);
}
```

</div>
</div>