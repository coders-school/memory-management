<!-- .slide: data-background="#111111" -->

# Szczegóły implementacyjne

___

### `std::unique_ptr<>`

* <!-- .element: class="fragment fade-in" --> To tylko "wrapper"
* <!-- .element: class="fragment fade-in" --> Trzyma zwykły wskaźnik
* <!-- .element: class="fragment fade-in" --> Konstruktor kopiuje wskaźnik (płytka kopia)
* <!-- .element: class="fragment fade-in" --> Destruktor woła odpowiedni <code>operator delete</code>
* <!-- .element: class="fragment fade-in" --> Brak operacji kopiowania
* <!-- .element: class="fragment fade-in" --> Przeniesienie oznacza:
  * <!-- .element: class="fragment fade-in" --> Skopiowanie wskaźników z obiektu źródłowego do docelowego
  * <!-- .element: class="fragment fade-in" --> Ustawienie wskaźników w obiekcie źródłowym na <code>nullptr</code>
* <!-- .element: class="fragment fade-in" --> Wszystkie metody są <code>inline</code>

___

### `std::shared_ptr<>`

<img src="../img/sharedptr2inverted.png" alt="sharedptr2" class="plain fragment fade-in">

* <!-- .element: class="fragment fade-in" --> Trzyma zwykły wskaźnik do obiektu
* <!-- .element: class="fragment fade-in" --> Trzyma też wskaźnik na współdzielony blok kontrolny zawierający:
  * <!-- .element: class="fragment fade-in" --> licznik shared_ptrów
  * <!-- .element: class="fragment fade-in" --> licznik weak_ptrów
  * <!-- .element: class="fragment fade-in" --> deleter
* <!-- .element: class="fragment fade-in" --> Destruktor:
  * <!-- .element: class="fragment fade-in" --> dekrementuje <code>shared-refs</code>
  * <!-- .element: class="fragment fade-in" --> usuwa obiekt gdy <code>shared-refs == 0</code>
  * <!-- .element: class="fragment fade-in" --> usuwa blok kontrolny, gdy <code>shared-refs == 0</code> i <code>weak-refs == 0</code>
* <!-- .element: class="fragment fade-in" --> Wszystkie metody są <code>inline</code>

___

### `std::shared_ptr<>`

* <!-- .element: class="fragment fade-in" --> Kopiowanie oznacza:
  * <!-- .element: class="fragment fade-in" --> Skopiowanie wskaźników
  * <!-- .element: class="fragment fade-in" --> Inkrementację <code>shared-refs</code>

<img src="../img/sharedptr3inverted.png" alt="sharedptr3" class="plain fragment fade-in">

* <!-- .element: class="fragment fade-in" --> Przeniesienie oznacza:
  * <!-- .element: class="fragment fade-in" --> Skopiowanie wskaźników
  * <!-- .element: class="fragment fade-in" --> Ustawienie wskaźników w obiekcie źródłowym na <code>nullptr</code>

<img src="../img/sharedptr4inverted.png" alt="sharedptr4" class="plain fragment fade-in">

___

### `std::weak_ptr<>`

* <!-- .element: class="fragment fade-in" --> Trzyma zwykły wskaźnik do obiektu
* <!-- .element: class="fragment fade-in" --> Trzyma też wskaźnik na współdzielony blok kontrolny zawierający:
  * <!-- .element: class="fragment fade-in" --> licznik shared_ptrów
  * <!-- .element: class="fragment fade-in" --> licznik weak_ptrów
  * <!-- .element: class="fragment fade-in" --> deleter
* <!-- .element: class="fragment fade-in" --> Destruktor:
  * <!-- .element: class="fragment fade-in" --> dekrementuje <code>weak-refs</code>
  * <!-- .element: class="fragment fade-in" --> usuwa blok kontrolny, gdy <code>shared-refs == 0</code> i <code>weak-refs == 0</code>

<img src="../img/sharedptr5inverted.png" alt="sharedptr5" class="plain fragment fade-in">

___

### `std::weak_ptr<>`

* <!-- .element: class="fragment fade-in" --> Kopiowanie oznacza:
  * <!-- .element: class="fragment fade-in" --> Skopiowanie wskaźników
  * <!-- .element: class="fragment fade-in" --> Inkrementację <code>weak-refs</code>

<img src="../img/sharedptr6inverted.png" alt="sharedptr6" class="plain fragment fade-in">

* <!-- .element: class="fragment fade-in" --> Przeniesienie oznacza:
  * <!-- .element: class="fragment fade-in" --> Skopiowanie wskaźników
  * <!-- .element: class="fragment fade-in" --> Ustawienie wskaźników w obiekcie źródłowym na <code>nullptr</code>

<img src="../img/sharedptr7inverted.png" alt="sharedptr7" class="plain fragment fade-in">

___

### `std::weak_ptr<>` + `std::shared_ptr<>`

* <!-- .element: class="fragment fade-in" -->Gdy mamy <code>shared_ptr</code> i <code>weak_ptr</code>

<img src="../img/sharedptr8inverted.png" alt="sharedptr8" class="plain fragment fade-in">

* <!-- .element: class="fragment fade-in" --> Po usunięciu <code>shared_ptr</code>

<img src="../img/sharedptr9inverted.png" alt="sharedptr9" class="plain fragment fade-in">

___

## Tworzenie `std::shared_ptr<>`

* <!-- .element: class="fragment fade-in" --> <code>std::shared_ptr&lt;Data&gt; p{new Data};</code>

<img src="../img/sharedptr10inverted.png" alt="sharedptr10" class="plain fragment fade-in">

* <!-- .element: class="fragment fade-in" --> <code>auto p = std::make_shared&lt;Data&gt;();</code>
  * <!-- .element: class="fragment fade-in" --> Mniejsze zużycie pamięci (w większości przypadków)
  * <!-- .element: class="fragment fade-in" --> Tylko jedna alokacja
  * <!-- .element: class="fragment fade-in" --> Cache-friendly

<img src="../img/sharedptr11inverted.png" alt="sharedptr11" class="plain fragment fade-in">
