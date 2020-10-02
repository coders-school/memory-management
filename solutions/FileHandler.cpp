#include <cstdio>
#include <cstdlib>
#include <iostream>

class FileOpeningError : public std::runtime_error {
public:
    FileOpeningError(std::string filename)
        : std::runtime_error("File opening failed: " + filename)
    {}
};

class FileHandler {
    FILE* fp_;
public:
    FileHandler(std::string filename)
        : fp_(std::fopen(filename.c_str(), "r"))
    {
        if (!fp_) {
            throw FileOpeningError{filename};
        }
    }

    FileHandler(const char* filename)
        : fp_(std::fopen(filename, "r"))
    {
        if (!fp_) {
            throw FileOpeningError{filename};
        }
    }

    ~FileHandler() {
        std::fclose(fp_);
    }

    friend std::ostream& operator<<(std::ostream& os, const FileHandler& fh);
};

std::ostream& operator<<(std::ostream& os, const FileHandler& fh) {
    char c;
    while ((c = std::fgetc(fh.fp_)) != EOF) { // standard C I/O file reading loop
       os << c;
    }

    if (std::ferror(fh.fp_)) {
        throw std::runtime_error("I/O error when reading");
    } else if (std::feof(fh.fp_)) {
        os << "End of file reached successfully\n";
    }

    return os;
}

int main() {
    int *wsk = new int{4};
    try {
        FileHandler fh{"../ResourceD.cpp"};
        std::cout << fh;
    } catch (FileOpeningError& foe) {
        std::cerr << foe.what() << '\n';
    } catch (std::runtime_error& re) {
        std::cerr << re.what() << '\n';
    }
    return 0;

}