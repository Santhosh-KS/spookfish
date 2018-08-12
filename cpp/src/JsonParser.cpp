#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include "JsonParser.hpp"

JsonParser::JsonParser(const std::string &file) :
  JsonFile(file)
{
  struct stat buffer;
  if ((stat(file.c_str(), &buffer) == 0)) {
    std::ifstream tmp(file);
    std::stringstream buffer;
    buffer << tmp.rdbuf();
    Jdoc.Parse(buffer.str().c_str());
    if (!Jdoc.IsObject()) {
      std::cerr << "ERROR: Invalid object. Json Syntax error in " << file.c_str() << "\n";
    }
  }
  else {
    std::cerr << "ERROR: File : " << file.c_str() << " not found.\n";
  }
}

JsonParser::~JsonParser()
{
  // Empty
}

std::string JsonParser::Value(const std::string &key)
{
  if (!HasMember(key)) {
    std::cerr << "ERROR: key \"" << key.c_str() << "\" not found in file " << JsonFile.c_str()<<"\n";
  }
  std::string retVal(Jdoc[key.c_str()].GetString());
  struct stat buffer;
  if ((stat(retVal.c_str(), &buffer) != 0)) {
    std::cerr << "ERROR: File \"" << retVal.c_str() << "\" Not found\n";
    std::cerr << "ERROR: please change the path values accordingly in \"" << JsonFile.c_str() << "\"\n";
  }
  return retVal;
}
