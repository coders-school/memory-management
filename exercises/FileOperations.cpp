#include <cstdio>
#include <cstdlib>
#include <iostream>

//wyjątek
class FileOpeningError : public std::runtime_error{
public:
    FileOpeningError(std::string fileName) : std::runtime_error("File opening failed: " + fileName) {}
};

class FileHandler{
private:
    std::string fileName_;
    FILE* fp_;
public:
    FileHandler(std::string fileName) : fileName_(fileName){
        fp_ = std::fopen(fileName_.c_str(), "r");
        if(!fp_){
            throw FileOpeningError{fileName};
        }
    }

    ~FileHandler(){
        std::fclose(fp_);
    }

    friend std::ostream& operator<<(std::ostream& os, const FileHandler& fH){
        char c;
        while((c = std::fgetc(fH.fp_)) != EOF){
            os << c;
        }
        if(std::ferror(fH.fp_))
            throw std::runtime_error("I/O error when reading");
        else if(std::feof(fH.fp_))
            os << "End of file reached successfully";

        return os;
    }
};


int main()
{
    try {
        FileHandler fh(std::string{"../ResourceD.cpp"});
        std::cout << fh;
    } catch(FileOpeningError& foe){
        std::cerr << foe.what() << '\n';
    } catch (std::runtime_error& re) {
        std::cerr << re.what() << '\n';
    }
    return 0;
}