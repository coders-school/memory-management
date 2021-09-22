# Pre-test 🤯

## Answers

___
<!-- .slide: style="font-size: 0.9em" -->
## 1. What is a problem with the below code?

```cpp
class Msg{};

void processMsg(Msg* msg)
{
    // ...
    delete msg;
}

int main()
{
    Msg m;
    processMsg(&m);
}
```

1. <!-- .element: class="fragment highlight-red" --> Freeing a heap allocated memory
2. <!-- .element: class="fragment highlight-green" --> Freeing a stack allocated memory
3. <!-- .element: class="fragment highlight-red" --> Freeing only a part of allocated memory
4. <!-- .element: class="fragment highlight-red" --> Dangling pointer

Note: 2

___

## 2. Mark true sentences


1. <!-- .element: class="fragment highlight-green" --> A reference works like a const pointer
2. <!-- .element: class="fragment highlight-red" --> A reference works like a pointer to const
3. <!-- .element: class="fragment highlight-green" --> A reference cannot be reassigned
4. <!-- .element: class="fragment highlight-red" --> <code>unique_ptr</code> can be copied
5. <!-- .element: class="fragment highlight-green" --> <code>shared_ptr</code> can be moved
6. <!-- .element: class="fragment highlight-red" --> <code>weak_ptr</code> can be created directly from the <code>unique_ptr</code>

Note: 1, 3, 5
