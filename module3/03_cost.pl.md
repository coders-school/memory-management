<!-- .slide: data-background="#111111" -->

## Czy wyjątki są drogie?

* [Moje film na YT z wyjaśnieniem](https://www.youtube.com/watch?v=quF1Jex0YL8)

* [Swobodny przebieg programu](https://quick-bench.com/q/6nZ33ylUe5VE2JE5QrqGP2y21VM)
* [Przebieg wyjątkowy](https://quick-bench.com/q/sKFj6SN0Jxx2l-beKR7JNNGh-uQ)

___

## Wyjątki

### Zalety
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Sygnalizacja i obsługa błędów może odbywać się oddzielnie
* <!-- .element: class="fragment fade-in" --> Czytelność kodu - funkcje mają tylko wymaganą logikę bez obsługi specjalnych przypadków
* <!-- .element: class="fragment fade-in" --> Błędy można obsługiwać w konstruktorach i operatorach
* <!-- .element: class="fragment fade-in" --> Brak dodatkowych sprawdzeń przy normalnym działaniu = brak dodatkowych if'ów = brak kosztów

### Wady
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Zwiększony rozmiar binarki (dodatkowy kod obsługi błędów jest dodawany na końcu wszystkich funkcji <code>noexcept</code>)
* <!-- .element: class="fragment fade-in" --> Czas obsługi wyjątków nie jest zdefiniowany
* <!-- .element: class="fragment fade-in" --> Zwykle wymaga informacji w czasie rzeczywistym, aby śledzić przepływ programu (zrzut rdzenia, debugger)

___

## Konkluzja

* <!-- .element: class="fragment fade-in" --> Czas obsługi wyjątków nie jest zdefiniowany
  * Zależy to od liczby i typów obiektów przydzielonych na stosie między miejscem, w którym wyjątek został zgłoszony, a momentem, w którym został faktycznie przechwycony
* <!-- .element: class="fragment fade-in" --> Nie używaj wyjątków w urządzeniach czasu rzeczywistego o ściśle określonym czasie wykonania (np. w systemach opieki zdrowotnej, motoryzacji)
* <!-- .element: class="fragment fade-in" --> Jeśli chcesz korzystać z wyjątków, sprawdź użycie programu. Jeśli wyjątkowy przepływ programu jest naprawdę rzadki - zmierz i porównaj, która wersja jest szybsza

___

## Zalecenia

* <!-- .element: class="fragment fade-in" --> Używaj wyjątków STL <a href="https://en.cppreference.com/w/cpp/error/exception">sprawdź cppreference.com</a>
* <!-- .element: class="fragment fade-in" --> Dziedzicz własne wyjątki z wyjątków STL
  * <code>catch(const std::exception & e)</code> złapie je wszystkie
* <!-- .element: class="fragment fade-in" --> Unikaj <code>catch(...)</code> - łapie absolutnie wszystko i zwykle nie jest dobrą praktyką
* <!-- .element: class="fragment fade-in" --> Łap wyjątki za pomocą <code>const &</code> - zapobiega zbędnym kopiom wyjątków
* <!-- .element: class="fragment fade-in" --> Używaj wyjątków tylko w nietypowych sytuacjach i nie twórz swobodnego przepływu programu na wyjątkach
* <!-- .element: class="fragment fade-in" --> Użyj słowa kluczowego <code>noexcept</code>, aby wskazać funkcje, z których wyjątek nie będzie generowany. Pomaga kompilatorowi w optymalizacji kodu i zmniejszeniu rozmiaru binarnego.
