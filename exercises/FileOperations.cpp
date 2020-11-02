#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

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

int main() {
    try {
    FileHandler fh("../ResourceD.cpp");
    std::cout << fh;
    } catch (FileOpeningError& foe) {
        std::cerr << foe.what();
    }
    std::fclose(fp);
}
