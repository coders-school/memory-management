#include "FileHandler.hpp"
#include <iostream>
#include <fstream>


FileHandler::FileHandler(std::string& directory):
directory_(directory){
myFile = new std::fstream;

  myFile->open (directory);
  if(myFile->is_open()){

  }
}


FileHandler::~FileHandler(){
    delete myFile;
}

#include <fstream>#include <string>class FileHandler {private: std::fstream file_; std::string fiilename_;public: FileHandler(std::string filename); ~FileHandler();
