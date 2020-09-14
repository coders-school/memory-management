#pragma once 
#include <string>



class FileHandler {


public:
FileHandler(std::string& directory);
~FileHandler();


private:
std::string directory_;
std::fstream* myFile;



};