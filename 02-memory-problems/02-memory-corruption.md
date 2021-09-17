## Memory corruption detection

* <!-- .element: class="fragment fade-in" --> Address Sanitizer (ASAN)
  * <!-- .element: class="fragment fade-in" --> dodaj flagi kompilacji:
    * <!-- .element: class="fragment fade-in" --> <code>–fsanitize=address -g</code>
    * <!-- .element: class="fragment fade-in" --> <code>–fsanitize=leak -g</code>
  * <!-- .element: class="fragment fade-in" --> uruchom program
* <!-- .element: class="fragment fade-in" --> Valgrind
  * <!-- .element: class="fragment fade-in" --> skompiluj program
  * <!-- .element: class="fragment fade-in" --> odpal go pod valgrindem:
    * <!-- .element: class="fragment fade-in" --> <code>valgrind /path/to/binary</code>
  * <!-- .element: class="fragment fade-in" --> użyj dodatkowych sprawdzeń:
    * <!-- .element: class="fragment fade-in" --> <code>valgrind --leak-check=full /path/to/binary</code>

Żadne nie działa na Windowsie 😕
<!-- .element: class="fragment fade-in" -->
