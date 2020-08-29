<!-- .slide: data-background="#111111" -->

# Inteligentne wskaźniki - podsumowanie

* <!-- .element: class="fragment fade-in" --> <code>#include &ltmemory&gt</code>
* <!-- .element: class="fragment fade-in" --> <code>std::unique_ptr<></code> do wyłącznego prawa własności
* <!-- .element: class="fragment fade-in" --> <code>std::shared_ptr<></code> dla współwłasności
* <!-- .element: class="fragment fade-in" --> <code>std::weak_ptr<></code> do obserwacji i przerywania cykli

___

## Ćwiczenie: ResourceFactory

1. <!-- .element: class="fragment fade-in" --> Skompiluj i uruchom aplikację ResourceFactory
2. <!-- .element: class="fragment fade-in" --> Umieść komentarze w miejscach, w których możesz zauważyć problemy
3. <!-- .element: class="fragment fade-in" --> Jak usunąć elementy z kolekcji (zasoby <code>vector&ltResource*&gt</code>)?
4. <!-- .element: class="fragment fade-in" --> Sprawdź wycieki pamięci
5. <!-- .element: class="fragment fade-in" --> Naprawić problemy
