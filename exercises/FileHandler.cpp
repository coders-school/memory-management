#include <string>
#include <iostream>

class FileOpeningError : public std::runtime_error {
public:
    FileOpeningError(std::string fileDirectory) 
        : std::runtime_error("File opening failed: " + fileDirectory)
    {}
};

class FileHandler {
    FILE* fp_;
public:
    FileHandler(std::string fileDirectory)
        : fp_(std::fopen(fileDirectory.c_str(), "r"))
    {
        if (!fp_) {
            throw FileOpeningError{fileDirectory};
        }
    }

    FileHandler(const char * fileDirectory)
        : fp_(std::fopen(fileDirectory, "r"))
    {}


    ~FileHandler() {
        std::fclose(fp_);
    }

    friend std::ostream& operator<<(std::ostream& os, const FileHandler& fh);
};

std::ostream& operator<<(std::ostream& os, const FileHandler& fh) {
    int c;
    while ((c = std::fgetc(fh.fp_)) != EOF) {
        os << c;
    }
    if (std::ferror(fh.fp_)) {
        throw std::runtime_error("I/O error when reading.");
    } else if (std::feof(fh.fp_)) {
        os << "End of file reached successfully" ;
    }

    return os;
}

int main() {
    try {
        FileHandler fh{"../ResourdeD.cpp"};
    } catch (FileOpeningError& foe) {
        std::cerr << foe.what();
    }
    return 0;
}