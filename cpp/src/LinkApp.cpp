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
#include "LinkApp.hpp"

LinkApp::LinkApp(std::string /*str*/):
  DataPathConfig("./data/bkup_DataPaths.json"),
  ClusterConfig("./data/bkup_ClusterConfig.json"),
  VideoCapture(std::make_unique<CaptureVideo>(DataPathConfig)),
  Cluster(std::make_unique<FaceCluster>(ClusterConfig))
{
  // Empty
}

LinkApp::~LinkApp()
{
  // Empty
}

int LinkApp::Run(std::string &link, std::string sessId)
{
  try {
    VideoCapture->Run(link, sessId);
    std::cout << "DOne with Run in LinkApp\n";
    // Enable clustering only when required.
    // TODO: Make it configurable.
    Cluster->Run(sessId);
  }
  catch(const std::exception& e ) {
    std::cerr << e.what() << "\n";
  }
  return 0;
}

int LinkApp::ClusterRun(std::string sessId)
{
  try {
    Cluster->Run(sessId);
  }
  catch(const std::exception& e ) {
    std::cerr << e.what() << "\n";
  }
  return 0;
}

int LinkApp::EnrollRun(std::string sessId)
{
  try {
    std::string imgFile("/tmp/images/" + sessId + "/enroll_images.txt");
    std::string lableFile("/tmp/images/" + sessId + "/lable_name.txt");
    if (Enroller.get() == nullptr) {
      Enroller  = std::make_unique<Enroll>(imgFile, lableFile);
    }
    Enroller->Run(sessId, imgFile, lableFile);
  }
  catch(const std::exception& e ) {
    std::cerr << e.what() << "\n";
  }
  return 0;
}
