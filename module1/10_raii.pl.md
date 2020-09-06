## RAII

<div class="multicolumn">
<div class="col">

* <!-- .element: class="fragment fade-in" --> Resource Acquisition Is Initialization (Pozyskiwanie zasobów to inicjalizacja)
  * <!-- .element: class="fragment fade-in" --> idiom / wzorzec w C++
  * <!-- .element: class="fragment fade-in" --> każdy zasób posiada klasę nim zarządzającą
  * <!-- .element: class="fragment fade-in" --> pozyskanie zasobu w konstruktorze
  * <!-- .element: class="fragment fade-in" --> zwolnienie zasobu w destruktorze
* <!-- .element: class="fragment fade-in" --> Korzyści
  * <!-- .element: class="fragment fade-in" --> krótszy kod (automatyzacja)
  * <!-- .element: class="fragment fade-in" --> wyraźna odpowiedzialność
  * <!-- .element: class="fragment fade-in" --> dotyczy wszelkich zasobów
  * <!-- .element: class="fragment fade-in" --> nie ma potrzeby tworzenia sekcji <code>finally</code>
  * <!-- .element: class="fragment fade-in" --> przewidywalne czasy zwalniania zasobu
  * <!-- .element: class="fragment fade-in" --> gwarancja poprawności na poziomie języka

</div>
<div class="col" style="font-size: 70%;margin-top: 70px;">

|             | Nabycie       | Wydanie          |
|:-----------:|:-------------:|:----------------:|
| pamięć      | new, new[]    | delete, delete[] |
| pliki       | fopen         | fclose           |
| blokady     | lock, try_lock| unlock           |
| gniazda     | socket        | close            |

</div>
<!-- .element: class="fragment fade-in" -->
