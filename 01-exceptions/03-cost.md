<!-- .slide: data-background="#111111" -->

## Czy wyjątki są kosztowne?

* [Moje wideo z wyjaśnieniem](https://www.youtube.com/watch?v=quF1Jex0YL8)
* [Zwykły przebieg programu](https://quick-bench.com/q/6nZ33ylUe5VE2JE5QrqGP2y21VM)
* [Przebieg z wyjątkiem](https://quick-bench.com/q/sKFj6SN0Jxx2l-beKR7JNNGh-uQ)

___

## Wyjątki

### Zalety
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Zgłaszanie błędów i ich obsługa są rozdzielone
* <!-- .element: class="fragment fade-in" --> Czytelność kodu wzrasta - można wyrzucić z funkcji logikę odpowiedzialną za nietypowe przypadki
* <!-- .element: class="fragment fade-in" --> Błędy można obsługiwać i zgłaszać w konstruktorach i operatorach
* <!-- .element: class="fragment fade-in" --> Brak dodatkowych sprawdzeń przy standardowym przebiegu programu = brak dodatkowych <code>if</code> = brak kosztu

### Wady
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Rozmiar binarki jest większy (kompilator dodaje dodatkowy kod na końcu każdej funkcji, która może uczestniczyć w obsłudze wyjątków)
* <!-- .element: class="fragment fade-in" --> Czas obsługi wyjątków jest niezdefiniowany
* <!-- .element: class="fragment fade-in" --> Zazwyczaj potrzebne są informacje z przebiegu programu aby śledzić jego przepływ (core dump, debugger)

___

## Wnioski

* <!-- .element: class="fragment fade-in" --> Czas obsługi wyjątków jest niezdefiniowany
  * Zależy od liczby, rozmiaru i typu danych na stosie pomiędzy miejscem rzucenia i obsługi wyjątku
* <!-- .element: class="fragment fade-in" --> Nie używamy wyjątków w systemach czasu rzeczywistego (RTOS) ze ściśle zdefiniowanym czasem wykonania funkcji (m.in. urządzenia medyczne, automotive)
* <!-- .element: class="fragment fade-in" --> Aby lepiej podjąć decyzję czy warto używać wyjątków należy zmierzyć sposób użycia programu. Jeśli ścieżki wyjątkowe występują bardzo rzadko to przejście na wyjątki może spowodować ogólny wzrost wydajności.

___

## Rekomendacje

* <!-- .element: class="fragment fade-in" --> Używaj wyjątków z STLa - <a href="https://en.cppreference.com/w/cpp/error/exception">zobacz na  cppreference.com</a>
* <!-- .element: class="fragment fade-in" --> Pisząc własne klasy wyjątków dziedzicz je po wyjątkach z STLa
  * <code>catch(const std::exception & e)</code> złapie je wszystkie
* <!-- .element: class="fragment fade-in" --> Unikaj <code>catch(...)</code> - to łapie absolutnie wszystko i nie jest to dobrą praktyką
* <!-- .element: class="fragment fade-in" --> Łap wyjątki przez <code>const &</code> - dzięki temu zapobiegasz niepotrzebnym kopiom obiektów wyjątków
* <!-- .element: class="fragment fade-in" --> Używaj wyjątków tylko w nietypowych sytuacjach i nie buduj standardowego przepływu programu w oparciu o wyjątki
* <!-- .element: class="fragment fade-in" --> Używaj słówka <code>noexcept</code>, aby wskazywać funkcje, które nie będą rzucać wyjątków. To pomaga kompilatorowi zoptymalizować program i zredukować rozmiar binarki.
