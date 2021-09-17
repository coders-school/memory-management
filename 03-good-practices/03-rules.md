## Zasada 0, Zasada 5

### Zasada 5 <!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Jeśli musisz ręcznie zaimplementować jedną z poniższych funkcji:
  * <!-- .element: class="fragment fade-in" --> destruktor
  * <!-- .element: class="fragment fade-in" --> konstruktor kopiujący
  * <!-- .element: class="fragment fade-in" --> kopiujący operator przypisania
  * <!-- .element: class="fragment fade-in" --> konstruktor przenoszący
  * <!-- .element: class="fragment fade-in" --> przenoszący operator przypisania
* <!-- .element: class="fragment fade-in" --> To najprawdopodobniej oznacza, że musisz zaimplementować je wszystkie.

### Zasada 0 <!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Jeśli używasz wrapperów RAII na zasoby, nie musisz implementować żadnej z powyższych 5 funkcji.

___

### Zasada 3

Ta zasada istniała przed C++11, gdy jeszcze nie było operacji przenoszenia. Była stosowana zamiast Zasady 5.

Warto wiedzieć, że Zasada 5 jest tylko optymalizacją Zasady 3. Jeśli nie zaimplementujemy operacji przenoszenia to tylko tracimy możliwość wydajniejszego działania programu.
