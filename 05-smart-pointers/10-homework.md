# Homework

___

## Pre-work

Przeczytaj artykuł [Semantyka przenoszenia](https://infotraining.bitbucket.io/cpp-11/move.html)

Przyda się do post-worku :)

___

## Post-work

(30 XP) Zaimplementuj swój własny `unique_ptr` (trochę uproszczony).

`unique_ptr` to klasa RAII, która:

* Jest klasą szablonową
* Trzyma wskaźnik do zarządzanego obiektu
* Konstruktor kopiuje wskaźnik
* Destruktor zwalnia pamięć
* Kopiowanie jest niedozwolone
* Przenoszenie jest dozwolone i oznacza:
  * Skopiowanie wskaźnika z obiektu źródłowego
  * Ustawienie wskaźnika w obiekcie źródłowym na `nullptr`
* Wymagane metody: `operator*()`, `operator->()`, `get()`, `release()`, `reset()`
* Nie zapomnij o testach (pokrycie >90%)

+3 XP za dostarczenie do 13.10.2020 włącznie
