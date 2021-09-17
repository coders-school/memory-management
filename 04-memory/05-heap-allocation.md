## Alokacja na stercie

<div class="multicolumn">
<div class="col" style="margin-top: 70px; font-size: 85%;">

Alokacja na stercie składa się z kilku kroków:
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> alokacji wskaźnika na stosie
* <!-- .element: class="fragment fade-in" --> alokacji <code>sizeof(T)</code> bajtów na stercie
* <!-- .element: class="fragment fade-in" --> wywołania konstruktora <code>T</code> na zaalokowanej pamięci
* <!-- .element: class="fragment fade-in" --> przypisania adresu do wskaźnika
* <!-- .element: class="fragment fade-in" --> manualnego zwolnienia pamięci używając operatora <code>delete</code>

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
