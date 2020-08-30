<!-- .slide: data-background="#111111" -->

# Szczegóły implementacji

___

### Szczegóły implementacji - `std::unique_ptr<>`

* <!-- .element: class="fragment fade-in" --> Tylko ramka do przechowywania
* <!-- .element: class="fragment fade-in" --> Zawiera wskaźnik obiektu
* <!-- .element: class="fragment fade-in" --> Konstruktor kopiuje wskaźnik
* <!-- .element: class="fragment fade-in" --> Wywołaj prawidłowe usuwanie w destruktorze
* <!-- .element: class="fragment fade-in" --> Bez kopiowania
* <!-- .element: class="fragment fade-in" --> Przeniesienie oznacza:
  * <!-- .element: class="fragment fade-in" --> Kopiowanie oryginalnego wskaźnika do nowego obiektu
  * <!-- .element: class="fragment fade-in" --> Ustawienie wskaźnika źródła na <code>nullptr</code>
* <!-- .element: class="fragment fade-in" --> Wszystkie metody są wbudowane

___

### Szczegóły implementacji – `std::shared_ptr<>`

<img data-src="img/sharedptr2inverted.png" alt="sharedptr2" class="plain fragment fade-in">

* <!-- .element: class="fragment fade-in" --> Zawiera wskaźnik obiektu
* <!-- .element: class="fragment fade-in" --> Mieści 2 liczniki referencyjne:
  * <!-- .element: class="fragment fade-in" --> liczący wspólne wskaźniki
  * <!-- .element: class="fragment fade-in" --> liczący słabe wskazówki
* <!-- .element: class="fragment fade-in" --> Destruktor:
  * <!-- .element: class="fragment fade-in" --> dekrementuje <code>shared-refs</code>
  * <!-- .element: class="fragment fade-in" --> usuwa dane użytkownika, gdy <code>shared-refs == 0</code>
  * <!-- .element: class="fragment fade-in" --> usuwa liczniki odwołań, gdy <code>shared-refs == 0</code> i <code>weak-refs == 0</code>
* <!-- .element: class="fragment fade-in" --> Extra space for a deleter
* <!-- .element: class="fragment fade-in" --> All methods are inline

___

### Szczegóły implementacji – `std::shared_ptr<>`

* <!-- .element: class="fragment fade-in" --> Kopiowanie oznacza:
  * <!-- .element: class="fragment fade-in" --> Kopiowanie wskaźników do celu
  * <!-- .element: class="fragment fade-in" --> Zwiększenie <code>shared-refs</code>

<img data-src="img/sharedptr3inverted.png" alt="sharedptr3" class="plain fragment fade-in">

* <!-- .element: class="fragment fade-in" --> Przenoszenie oznacza:
  * <!-- .element: class="fragment fade-in" --> Kopiowanie wskaźników do celu
  * <!-- .element: class="fragment fade-in" --> Ustawianie wskaźników źródłowych na <code>nullptr</code>

<img data-src="img/sharedptr4inverted.png" alt="sharedptr4" class="plain fragment fade-in">

___

### Szczegóły implementacji – `std::weak_ptr<>`

* <!-- .element: class="fragment fade-in" --> Zawiera wskaźnik obiektu
* <!-- .element: class="fragment fade-in" --> Mieści 2 liczniki referencyjne:
  * <!-- .element: class="fragment fade-in" --> zliczający wspólne wskaźniki
  * <!-- .element: class="fragment fade-in" --> zliczający słabe wskaźniki
* <!-- .element: class="fragment fade-in" --> Destruktor:
  * <!-- .element: class="fragment fade-in" --> dekrementuje <code>weak-refs</code>
  * <!-- .element: class="fragment fade-in" --> usuwa liczniki odwołań, gdy <code>shared-refs == 0</code> i <code>weak-refs == 0</code>

<img data-src="img/sharedptr5inverted.png" alt="sharedptr5" class="plain fragment fade-in">

___

### Szczegóły implementacji – `std::weak_ptr<>`

* <!-- .element: class="fragment fade-in" --> Kopiowanie oznacza:
  * <!-- .element: class="fragment fade-in" --> kopiowanie wskaźników do celu
  * <!-- .element: class="fragment fade-in" --> zwiększenie <code>weak-refs</code>

<img data-src="img/sharedptr6inverted.png" alt="sharedptr6" class="plain fragment fade-in">

* <!-- .element: class="fragment fade-in" --> Przenoszenie oznacza:
  * <!-- .element: class="fragment fade-in" --> kopiowanie wskaźników do celu
  * <!-- .element: class="fragment fade-in" --> Ustawianie wskaźników źródłowych na <code>nullptr</code>

<img data-src="img/sharedptr7inverted.png" alt="sharedptr7" class="plain fragment fade-in">

___

### `std::weak_ptr<>` + `std::shared_ptr<>`

* <!-- .element: class="fragment fade-in" --> Posiadanie wspólnego wskaźnika i słabego wskaźnika

<img data-src="img/sharedptr8inverted.png" alt="sharedptr8" class="plain fragment fade-in">

* <!-- .element: class="fragment fade-in" --> Po usunięciu wspólnego wskaźnika

<img data-src="img/sharedptr9inverted.png" alt="sharedptr9" class="plain fragment fade-in">

___

## Making a `std::shared_ptr<>`

* <!-- .element: class="fragment fade-in" --> <code>std::shared_ptr&ltData&gt p{new Data};</code>

<img data-src="img/sharedptr10inverted.png" alt="sharedptr10" class="plain fragment fade-in">

* <!-- .element: class="fragment fade-in" --> <code>auto p = std::make_shared&ltData&gt();</code>
  * <!-- .element: class="fragment fade-in" --> Mniej pamięci (najprawdopodobniej)
  * <!-- .element: class="fragment fade-in" --> Tylko jeden przydział
  * <!-- .element: class="fragment fade-in" --> Przyjazny dla pamięci podręcznej

<img data-src="img/sharedptr11inverted.png" alt="sharedptr11" class="plain fragment fade-in">
