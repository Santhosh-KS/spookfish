#ifndef JSON_WRITER_HPP
#define JSON_WRITER_HPP

#include<string>

#include "NotCopyable.hpp"
#include "JsonParser.hpp"

class JsonWriter: public NotCopyable
{
  private:
    const std::string JsonFile;
    //JsonParser Parser;
    JsonWriter();
  public:
    JsonWriter(const std::string &);
    ~JsonWriter();
    inline std::string File() {return JsonFile; };
};

#endif // JSON_WRITER_HPP
