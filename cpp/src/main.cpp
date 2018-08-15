#include <iostream>

#include "CaptureVideo.hpp"
#include "JsonParser.hpp"


#define SKIP_FRAMES 10

int main(int argc, char** argv)
{
  auto jsonFile("../data/bkup_DataPaths.json");
  JsonParser parser(jsonFile);
  auto videoFile(parser.Value("TestVideoFile"));
  //auto videoFile("/home/santhosh/course/final_project/cpp/data/got_1.mp4");
  uint16_t skipRate(10);
  try {
    CaptureVideo vidCapture(videoFile, skipRate);
    vidCapture.Run();
    //std::cout << "Out of run\n";
  }
  catch(const std::exception& e ) {
    std::cerr << e.what() << "\n";
  }
  //std::cout << "Before main exit\n";
  return 0;
}
