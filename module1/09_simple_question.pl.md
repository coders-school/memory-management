## Proste pytanie…

Ile jest tutaj możliwych ścieżek wykonania programu?

```cpp
String EvaluateSalaryAndReturnName(Employee e)
{
    if( e.Title() == "CEO" || e.Salary() > 100000 )
    {
        cout << e.First() << " " << e.Last()
             << " is overpaid" << endl;
    }
    return e.First() + " " + e.Last();
}

```

* <!-- .element: class="fragment fade-in" --> 23 (dwadzieścia trzy)
* <!-- .element: class="fragment fade-in" --> Powodem są wyjątki
* <!-- .element: class="fragment fade-in" --> Przykład: Herb Sutter, <a href="http://www.gotw.ca/gotw/020.htm">GotW#20</a>
