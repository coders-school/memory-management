<!-- .slide: data-background="#111111" -->

# Inteligentne wskaźniki - podsumowanie

* <!-- .element: class="fragment fade-in" --> <code>#include &lt;memory&gt;</code>
* <!-- .element: class="fragment fade-in" --> <code>std::unique_ptr<></code> dla wyłącznej własności
* <!-- .element: class="fragment fade-in" --> <code>std::shared_ptr<></code> dla współdzielonej własności
* <!-- .element: class="fragment fade-in" --> <code>std::weak_ptr<></code> do obserwowania i przerywania cykli

___

## Zadanie: ResourceFactory

1. <!-- .element: class="fragment fade-in" --> Skompiluj i uruchom program ResourceFactory
2. <!-- .element: class="fragment fade-in" --> Czy zauważasz problematyczne miejsca? Oznacz je komentarzami w kodzie.
3. <!-- .element: class="fragment fade-in" --> Jak usuwać elementy z kolekcji (<code>vector&lt;Resource*&gt;</code> resources)?
4. <!-- .element: class="fragment fade-in" --> Uruchom program pod valgrindem
5. <!-- .element: class="fragment fade-in" --> Napraw problemy
