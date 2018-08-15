#ifndef STATS_HPP
#define STATS_HPP

#include <vector>
#include <string>
#include <memory>
#include "NotCopyable.hpp"
#include "JsonParser.hpp"

class Stats: public NotCopyable
{
  private:
    std::string VideoFile;
    std::string JsonOutputFile;
    std::string StartTime;
    std::string EndTime;
    uint64_t StartTimeEpoch;
    uint64_t EndTimeEpoch;
    uint64_t TotalImagesCaptured;
    std::vector<std::string> ImageListVec;
    std::unique_ptr<JsonParser> Parser;
    Stats();
  public:
    Stats(const std::string &vidFile, const std::string &);
    ~Stats();
    bool Sync(std::string &file, uint64_t count);
    bool CheckImageCount(uint64_t count);
    bool CheckStartTimeEpoch();
    bool CheckEndTimeEpoch();
    bool CheckEndTime();
    bool CheckStartTime();
    bool CheckParser(std::string &file);
};

#endif // STATS_HPP
