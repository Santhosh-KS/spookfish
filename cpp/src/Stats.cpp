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


#include <ctime>
#include <chrono>
#include <iostream>
#include "Stats.hpp"

Stats::Stats(const std::string &vidFile, const std::string &jsonOutFile):
  VideoFile(vidFile),
  JsonOutputFile(jsonOutFile),
  StartTime(""),
  EndTime(""),
  StartTimeEpoch(0),
  EndTimeEpoch(0),
  TotalImagesCaptured(0)
{
  // Empty
}

Stats::~Stats()
{
  if(CheckParser(JsonOutputFile)) {
    CheckStartTimeEpoch();
    CheckStartTimeEpoch();
    CheckEndTime();
    CheckStartTime();
  }
  Parser.reset();
}

bool Stats::Sync(std::string &file, uint64_t count)
{
  if(CheckParser(file)) {
    CheckStartTime();
    CheckEndTime();
    CheckStartTimeEpoch();
    CheckStartTimeEpoch();
    CheckImageCount(count);
  }
  return false;
}

bool Stats::CheckParser(std::string &file)
{
  if (Parser.get() == nullptr) {
    Parser = std::make_unique<JsonFileParser>(file);
    if (Parser.get() == nullptr) {
      std::cerr << "Failed to create JsonFileParser object\n";
      return false;
    }
  }
  return true;
}

bool Stats::CheckStartTime()
{
  auto str("StartTime");
  if (Parser->HasMember(str)) {
    std::string val("January 1, 1970");
    if (val.compare(Parser->GetString(str)) == 0) {
      std::time_t result = std::time(nullptr);
      std::string newVal(std::asctime(std::localtime(&result)));
      return Parser->SetString(str, newVal);
    }
  }
  return true;
}

bool Stats::CheckEndTime()
{
  auto str("EndTime");
  if (Parser->HasMember(str)) {
    std::time_t result = std::time(nullptr);
    std::string newVal(std::asctime(std::localtime(&result)));
    return Parser->SetString(str, newVal);
  }
  return false;
}

bool Stats::CheckStartTimeEpoch()
{
  auto str("StartTimeEpoch");
  if (Parser->HasMember(str)) {
    std::string val("0");
    if (val.compare(Parser->GetString(str)) == 0) {
      using namespace  std::chrono;
      milliseconds ms = duration_cast< milliseconds >
        (system_clock::now().time_since_epoch());
      return Parser->SetString(str, std::to_string(ms.count()));
    }
  }
  return true;
}

bool Stats::CheckEndTimeEpoch()
{
  auto str("EndTimeEpoch");
  if (Parser->HasMember(str)) {
    using namespace  std::chrono;
    milliseconds ms = duration_cast< milliseconds >
      (system_clock::now().time_since_epoch());
    return Parser->SetString(str, std::to_string(ms.count()));
  }
  return false;
}

bool Stats::CheckImageCount(uint64_t count)
{
  auto str("TotalImagesCaptured");
  if (Parser->HasMember(str)) {
    return Parser->SetUInt64(str, count);
  }
  return false;
}
