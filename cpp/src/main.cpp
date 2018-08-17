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
