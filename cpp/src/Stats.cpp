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
    Parser = std::make_unique<JsonParser>(file);
    if (Parser.get() == nullptr) {
      std::cerr << "Failed to create JsonParser object\n";
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
