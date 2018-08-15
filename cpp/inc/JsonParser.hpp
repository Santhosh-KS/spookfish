#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include<string>

#include "NotCopyable.hpp"
#include "rapidjson/document.h"

class JsonParser: public NotCopyable
{
private:
  const std::string JsonFile;
  rapidjson::Document Jdoc;
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
//  inline bool IsUInt64(const std::string &str) { return Jdoc[str.c_str()].IsUInt64(); }
  inline bool IsDouble(const std::string &str) { return Jdoc[str.c_str()].IsDouble(); }
  inline std::string FileName() { return JsonFile;}
  std::string Value(const std::string &key);
  std::string GetString(const std::string &key);
  inline uint64_t GetUInt64(const std::string &key) { return Jdoc[key.c_str()].GetUint64(); }
  bool SetString(const std::string &key, const std::string &newVal);
  bool SetUInt64(const std::string &key, uint64_t);
};

#endif // JSON_PARSER_HPP
