#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include<string>

#include "rapidjson/document.h"

class JsonParser
{
private:
  std::string JsonFile;
  rapidjson::Document Jdoc;
public:
  JsonParser(std::string &file);
  ~JsonParser();
  inline bool IsObject(){ return Jdoc.IsObject(); }
  inline bool HasMember(std::string &str) { return Jdoc.HasMember(str.c_str()); }
  inline bool IsString(std::string &str) { return Jdoc[str.c_str()].IsString(); }
  inline bool IsBool(std::string &str) { return Jdoc[str.c_str()].GetBool(); }
  inline bool IsNull(std::string &str) { return Jdoc[str.c_str()].IsNull(); }
  inline bool IsNumber(std::string &str) { return Jdoc[str.c_str()].IsNumber(); }
  inline bool IsInt(std::string &str) { return Jdoc[str.c_str()].IsInt(); }
  inline bool IsDouble(std::string &str) { return Jdoc[str.c_str()].IsDouble(); }
};

#endif // JSON_PARSER_HPP
