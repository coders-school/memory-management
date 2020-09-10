<!-- .slide: data-background="#111111" -->

## Are exceptions expensive?

* [My YT video with explanation (in Polish)](https://www.youtube.com/watch?v=quF1Jex0YL8)

* [Casual program flow](https://quick-bench.com/q/6nZ33ylUe5VE2JE5QrqGP2y21VM)
* [Exceptional flow](https://quick-bench.com/q/sKFj6SN0Jxx2l-beKR7JNNGh-uQ)

___

## Exceptions

### Advantages
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Error signalling and handling can be done separately
* <!-- .element: class="fragment fade-in" --> Code readability - functions have only required logic without handling special cases
* <!-- .element: class="fragment fade-in" --> Errors can be handled in constructors and operators
* <!-- .element: class="fragment fade-in" --> No extra checks on casual flow = no extra if = no cost

### Disadvantages
<!-- .element: class="fragment fade-in" -->

* <!-- .element: class="fragment fade-in" --> Binary size is increased (extra error handling code is added in the end of all <code>noexcept</code> functions)
* <!-- .element: class="fragment fade-in" --> Time of exception handling is not defined
* <!-- .element: class="fragment fade-in" --> Usually requires real-time information to track the program flow (core dump, debugger)

___

## Conclusions

* <!-- .element: class="fragment fade-in" --> Time of exception handling is not defined
  * It depends on the number and types of objects allocated on stack between the place where the exception was thrown and when it was actually caught
* <!-- .element: class="fragment fade-in" --> Do not use exceptions in real-time devices with strictly defined time of execution (eg. in healthcare systems, automotive)
* <!-- .element: class="fragment fade-in" --> If you want to use exceptions check the usage of the program. If exceptional program flow is really rare - measure and benchmark which version is faster

___

## Recommendations

* <!-- .element: class="fragment fade-in" --> Use STL exceptions <a href="https://en.cppreference.com/w/cpp/error/exception">check cppreference.com</a>
* <!-- .element: class="fragment fade-in" --> Inherit own exceptions from STL exceptions
  * <code>catch(const std::exception & e)</code> will catch all of them
* <!-- .element: class="fragment fade-in" --> Avoid <code>catch(...)</code> - it catches absolutely everything and usually is not a good practice
* <!-- .element: class="fragment fade-in" --> Catch exceptions by <code>const &</code> - it prevents redundant exception copies
* <!-- .element: class="fragment fade-in" --> Use exceptions only in unusual situations and do not build a casual program flow on exceptions
* <!-- .element: class="fragment fade-in" --> Use <code>noexcept</code> keyword to indicate functions from which the exception will not be thrown. It helps a compiler to optimize the code and reduce a binary size.
