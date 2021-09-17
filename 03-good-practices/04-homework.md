# Praca domowa 💻

___

## Post-work

* Zadanie `file-wrapper` (12 XP)

### Bonusy

* 3 XP za dostarczenie do 03.10.2021 23:59
* 1 XP za pracę w grupie

[Zadania w repo](https://github.com/coders-school/memory-management/tree/master/03-good-practices/04-homework.md)

___
<!-- .slide: style="font-size: 0.9em" -->

## FileWrapper

Pamiętasz klasę `FileWrapper` z lekcji o obsłudze błędów?

```cpp
struct FileWrapper {
    FileWrapper(std::string const& filePath)
            : m_file(fopen(filePath.c_str(), "rw")) {
        /* What if the file did not open? */
    }

    FileWrapper & operator<<(std::string const& text) {
        /* What if the file did not open? */
        fputs(text.c_str(), m_file);
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const FileHandler& fh);

private:
    FILE* m_file;
};
```

___

Dopisz implementację klasy `FileWrapper` zgodną z RAII. Pamiętaj o:

* rzuceniu wyjątku, jeśli nie udało się otworzyć pliku
* pozyskaniu zasobu w konstruktorze
* zwolnieniu zasobu w destruktorze
* zasadzie 5

Przetestuj:

* otwieranie istniejących plików
* otwieranie nieistniejących plików
* otwieranie katalogów
* otwieranie plików do których nie masz uprawnień
* odczyt z pliku
* zapis do pliku
* wycieki pamięci
