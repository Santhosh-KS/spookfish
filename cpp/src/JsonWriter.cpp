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


#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <sys/stat.h>
#include "JsonWriter.hpp"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


// Sample stats json file.
/*
   [
   {
   "VideoFile"           : "/opt/test_vid1.mp4"
   "StartTime"           : "Wed Sep 21 10:27:52 2011",
   "StartTimeEpoch"      : "1345667999"
   "TotalImagesCaptured" : 1234,
   "ListOfImageFiles"    : ["1.jpg","2.jpg","3.jpg"]
   "EndTime"             : "Wed Sep 21 10:28:52 2011",
   "EndTimeEpoch"        : "1316615372"
   },
   {
   "VideoFile"           : "/opt/test_vid2.mp4"
   "StartTime"           : "Wed Sep 22 10:27:52 2011",
   "StartTimeEpoch"      : "1316615272",
   "TotalImagesCaptured" : 5678,
   "ListOfImageFiles"    : ["1.jpg","2.jpg","3.jpg"]
   "EndTime"             : "Wed Sep 22 10:28:52 2011",
   "EndTimeEpoch"        : "1316615372"
   }
   ]
   */

JsonWriter::JsonWriter(const std::string &file)
{
  rapidjson::StringBuffer jsonBuffer;
  rapidjson::Writer<rapidjson::StringBuffer> writer(jsonBuffer);

  writer.StartObject();
  writer.Key("VideoFile");
  writer.String(".mp4");
  writer.Key("StartTime");
  writer.String("January 1, 1970");
  writer.Key("StartTimeEpoch");
  writer.String("0");
  writer.Key("TotalImagesCaptured");
  writer.Uint64(0);
  writer.Key("ListOfImageFiles");
  writer.StartArray();
  for (unsigned i = 0; i < 2; i++) {
    writer.String(std::to_string(i).c_str());
  }
  writer.EndArray();
  writer.Key("EndTime");
  writer.String("January 1, 1970");
  writer.Key("EndTimeEpoch");
  writer.String("0");
  writer.EndObject();

  std::ofstream outFile;
  outFile.open(file);
  outFile << jsonBuffer.GetString();
  outFile.close();
}

JsonWriter::~JsonWriter()
{
  // Empty
}
