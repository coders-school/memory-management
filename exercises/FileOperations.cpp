#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

<<<<<<< HEAD
class FileOpeningError : public std::runtime_error {
    public:
    FileOpeningError(std::string path)
    : std::runtime_error("File opening failed: " + path)
    {}
};

class FileHandler {
public:
    FileHandler(std::string path) {
        file_ = std::fopen(path.c_str(), "r");
        if (!file_) {
            throw FileOpeningError(path);
        }
    }
    ~FileHandler() {
        std::fclose(file_);
=======
int main()
{
    FILE* fp = std::fopen("thisFileDoesNotExist.cpp", "r");
    if(!fp) {
        std::perror("File opening failed");
        return EXIT_FAILURE;
>>>>>>> 9addd5891723a1d66eecbe4dfdc328007e9895c7
    }

    friend std::ostream& operator<<(std::ostream& out, const FileHandler& f) {
        char c;
        if (!f.file_) {
            return out;
        }
        while ((c = std::fgetc(f.file_)) != EOF) {
            out << c;
        }

        if (std::ferror(f.file_))
            out << "I/O error when reading";
        else if (std::feof(f.file_))
            out << "End of file reached successfully";
        return out;
    }

private:
    FILE* file_ = nullptr;
};

<<<<<<< HEAD
int main() {
    try {
    FileHandler fh("../ResourceD.cpp");
    std::cout << fh;
    } catch (FileOpeningError& foe) {
        std::cerr << foe.what();
    }
=======
    std::fclose(fp);
>>>>>>> 9addd5891723a1d66eecbe4dfdc328007e9895c7
}
