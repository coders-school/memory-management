<!-- .slide: data-background="#111111" -->

# Smart pointers

___

## Inteligentne wskaźniki

* <!-- .element: class="fragment fade-in" --> Inteligentny wskaźnik zarządza zwykłym wskaźnikiem do pamięci zaalokowanej na stercie

  * <!-- .element: class="fragment fade-in" --> Usuwa wskazywany obiekt we właściwym czasie
  * <!-- .element: class="fragment fade-in" --> <code>operator->()</code> woła metody wskazywanego obiektu
  * <!-- .element: class="fragment fade-in" --> <code>operator.()</code> woła metody inteligentnego wskaźnika
  * <!-- .element: class="fragment fade-in" --> inteligentny wskaźnik na klasę bazową może wskazywać na obiekt klasy pochodnej (działa polimorfizm)

* <!-- .element: class="fragment fade-in" --> Inteligentne wskaźniki w STLu:

  * <!-- .element: class="fragment fade-in" --> <code>std::unique_ptr<></code>
  * <!-- .element: class="fragment fade-in" --> <code>std::shared_ptr<></code>
  * <!-- .element: class="fragment fade-in" --> <code>std::weak_ptr<></code>
  * <!-- .element: class="fragment fade-in" --> <code>std::auto_ptr<></code> - usunięty w C++17 (na szczęście)
