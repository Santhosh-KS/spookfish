#include "JsonParser.hpp"

JsonParser::JsonParser(std::string &file) :
  JsonFile(file)
{
  Jdoc.Parse(file.c_str());
  assert(Jdoc.IsObject());
}

JsonParser::~JsonParser()
{
  // Empty
}

#if 0
assert(document["hello"].IsString());
printf("hello = %s\n", document["hello"].GetString());

assert(document["t"].IsBool());
printf("t = %s\n", document["t"].GetBool() ? "true" : "false");

printf("n = %s\n", document["n"].IsNull() ? "null" : "?");

assert(document["i"].IsNumber());
// In this case, IsUint()/IsInt64()/IsUInt64() also return true.
assert(document["i"].IsInt());
printf("i = %d\n", document["i"].GetInt());

// Alternative (int)document["i"]
assert(document["pi"].IsNumber());
assert(document["pi"].IsDouble());
printf("pi = %g\n", document["pi"].GetDouble());

// Using a reference for consecutive access is handy and faster.
const Value& a = document["a"];
assert(a.IsArray());
for (SizeType i = 0; i < a.Size(); i++) // Uses SizeType instead of size_t
printf("a[%d] = %d\n", i, a[i].GetInt());

for (auto& v : a.GetArray())
      printf("%d ", v.GetInt());

#endif
