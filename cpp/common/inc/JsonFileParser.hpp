#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

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

#include<string>

#include "NotCopyable.hpp"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

class JsonFileParser: public NotCopyable
{
private:
  const std::string JsonFile;
  rapidjson::Document Jdoc;
public:
  explicit JsonFileParser(const std::string &file);
  ~JsonFileParser();
  inline bool IsObject(){ return Jdoc.IsObject(); }
  inline bool HasMember(const std::string &str) { return Jdoc.HasMember(str.c_str()); }
  inline bool IsString(const std::string &str) { return Jdoc[str.c_str()].IsString(); }
  inline bool IsBool(const std::string &str) { return Jdoc[str.c_str()].GetBool(); }
  inline bool IsNull(const std::string &str) { return Jdoc[str.c_str()].IsNull(); }
  inline bool IsNumber(const std::string &str) { return Jdoc[str.c_str()].IsNumber(); }
  inline bool IsInt(const std::string &str) { return Jdoc[str.c_str()].IsInt(); }
//  inline bool IsUInt64(const std::string &str) { return Jdoc[str.c_str()].IsUInt64(); }
  inline bool IsDouble(const std::string &str) { return Jdoc[str.c_str()].IsDouble(); }
  inline std::string FileName() { return JsonFile;}
  std::string Value(const std::string &key);
  std::string GetString(const std::string &key);
  inline uint64_t GetUInt64(const std::string &key) { return Jdoc[key.c_str()].GetUint64(); }
  bool SetString(const std::string &key, const std::string &newVal);
  bool SetUInt64(const std::string &key, uint64_t);

  std::string GetStrigifiedJson();
};

#endif // JSON_PARSER_HPP
