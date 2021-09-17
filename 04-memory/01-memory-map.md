## Mapa pamięci procesu

* <!-- .element: class="fragment fade-in" --> .text - kod programu
* <!-- .element: class="fragment fade-in" --> .rodata - dane tylko do odczytu
* <!-- .element: class="fragment fade-in" --> .data - dane do odczytu i zapisu, zmienne globalne i statyczne
* <!-- .element: class="fragment fade-in" --> .bss - block started by symbol = zero-initialized data
* <!-- .element: class="fragment fade-in" --> sterta (heap) - dynamicznie zaalokowana pamięć
* <!-- .element: class="fragment fade-in" --> stos (stack) - stos wywołań - adresy powrotu, parametry funkcji, zmienne lokalne, tymczasowe dane

<p style="text-align: center">
    <img height="300" src="../img/memory.png" alt="memory map" class="plain">
</p>
<!-- .element: class="fragment fade-in" -->
