#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include<string>

#include "rapidjson/document.h"

class JsonParser
{
private:
  const std::string JsonFile;
  rapidjson::Document Jdoc;
  JsonParser();
public:
  explicit JsonParser(const std::string &file);
  ~JsonParser();
  inline bool IsObject(){ return Jdoc.IsObject(); }
  inline bool HasMember(const std::string &str) { return Jdoc.HasMember(str.c_str()); }
  inline bool IsString(const std::string &str) { return Jdoc[str.c_str()].IsString(); }
  inline bool IsBool(const std::string &str) { return Jdoc[str.c_str()].GetBool(); }
  inline bool IsNull(const std::string &str) { return Jdoc[str.c_str()].IsNull(); }
  inline bool IsNumber(const std::string &str) { return Jdoc[str.c_str()].IsNumber(); }
  inline bool IsInt(const std::string &str) { return Jdoc[str.c_str()].IsInt(); }
  inline bool IsDouble(const std::string &str) { return Jdoc[str.c_str()].IsDouble(); }
  inline std::string FileName() { return JsonFile;}
  std::string Value(const std::string &key);
};

#endif // JSON_PARSER_HPP
