/*
   MIT License

   Copyright (c) 2018 santhoshachar08@gmail.com

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/


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
  if (key.compare("SkipFrame") != 0 && key.compare("StorageEnabled") != 0) {
    struct stat buffer;
    if ((stat(retVal.c_str(), &buffer) != 0)) {
      std::cerr << "ERROR: File \"" << retVal.c_str() << "\" Not found\n";
      std::cerr << "ERROR: please change the path values accordingly in \"" << JsonFile.c_str() << "\"\n";
    }
  }
  return retVal;
}

std::string JsonParser::GetString(const std::string &key)
{
  return Value(key);
}

bool JsonParser::SetString(const std::string &key, const std::string &newVal)
{
  if (!HasMember(key)) {
    std::cerr << "ERROR: key \"" << key.c_str() << "\" not found in file " << JsonFile.c_str()<<"\n";
    return false;
  }
  Jdoc[key.c_str()].SetString(newVal.c_str(),newVal.length());
  return true;
}

bool JsonParser::SetUInt64(const std::string &key,uint64_t count)
{
  if (!HasMember(key)) {
    std::cerr << "ERROR: key \"" << key.c_str() << "\" not found in file " << JsonFile.c_str()<<"\n";
    return false;
  }
  Jdoc[key.c_str()].SetUint64(count);
  return true;
}

std::string JsonParser::GetStrigifiedJson()
{
  //printf("\nModified JSON with reformatting:\n");
  rapidjson::StringBuffer sb;
  rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
  Jdoc.Accept(writer);    // Accept() traverses the DOM and generates Handler events.
  //std::cout << "stringify : " << sb.GetString() << "\n";
  return sb.GetString();
}
