#ifndef STATS_HPP
#define STATS_HPP

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
