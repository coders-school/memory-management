## Przepełnienie stosu

* Istnieje ograniczenie rozmiaru stosu (zależne od systemu operacyjnego)

```cpp
int foo()
{
    double x[1048576];
    x[0] = 10;
    return 0;
}

int main()
{
    foo();
    return 0;
}
```
