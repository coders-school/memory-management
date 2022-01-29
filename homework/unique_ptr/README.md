# `unique_ptr`

(30 XP) Zaimplementuj swój własny unique_ptr (trochę uproszczony).

unique_ptr to klasa RAII, która:

- Jest klasą szablonową
- Trzyma wskaźnik do zarządzanego obiektu
- Konstruktor kopiuje wskaźnik
- Destruktor zwalnia pamięć
- Kopiowanie jest niedozwolone
- Przenoszenie jest dozwolone i oznacza:
  - Skopiowanie wskaźnika z obiektu źródłowego
  - Ustawienie wskaźnika w obiekcie źródłowym na nullptr
- Wymagane metody: operator*(), operator->(), get(), release(), reset()
- Nie zapomnij o testach (pokrycie >90%)
