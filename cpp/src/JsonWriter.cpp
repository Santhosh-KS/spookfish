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
