## RAII

<div class="multicolumn">
<div class="col">

* <!-- .element: class="fragment fade-in" --> Resource Acquisition Is Initialization
  * <!-- .element: class="fragment fade-in" --> idiom / wzorzec w C++
  * <!-- .element: class="fragment fade-in" --> każdy zasób ma właściciela
  * <!-- .element: class="fragment fade-in" --> acquired in constructor
  * <!-- .element: class="fragment fade-in" --> released in destructor
* <!-- .element: class="fragment fade-in" --> Zalety
  * <!-- .element: class="fragment fade-in" --> krótszy kod
  * <!-- .element: class="fragment fade-in" --> jasna odpowiedzialność
  * <!-- .element: class="fragment fade-in" --> można stosować do dowolnych zasobów
  * <!-- .element: class="fragment fade-in" --> nie potrzeba sekcji <code>finally</code>
  * <!-- .element: class="fragment fade-in" --> przewidywalne czasy zwalniania
  * <!-- .element: class="fragment fade-in" --> poprawność gwarantowana przez sam język

</div>
<div class="col" style="font-size: 70%;margin-top: 70px;">

|             | Acquire       | Release          |
|:-----------:|:-------------:|:----------------:|
| memory      | new, new[]    | delete, delete[] |
| files       | fopen         | fclose           |
| locks       | lock, try_lock| unlock           |
| sockets     | socket        | close            |

</div>
<!-- .element: class="fragment fade-in" -->
