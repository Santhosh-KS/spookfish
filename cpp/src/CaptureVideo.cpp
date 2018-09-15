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
#include <stdexcept>

#include "CaptureVideo.hpp"
#include "DlibHandler.hpp"


CaptureVideo::CaptureVideo(const std::string &configFile):
  Parser(std::make_unique<JsonFileParser>(configFile)),
  ShapePredictFile(Parser->Value("PredictorFile")),
  FaceRecRsNetFile(Parser->Value("FaceRecModelFile")),
  LabelFile(Parser->Value("LabelFile")),
  FaceDescriptorFile(Parser->Value("DescriptorFile")),
  VideoFile(Parser->Value("TestVideoFile")),
  SkipFrame(std::stoi(Parser->Value("SkipFrame"))),
  VidCapture(std::make_unique<cv::VideoCapture>(VideoFile))
{
  if (!VidCapture->isOpened()) {
    VidCapture.release();
    throw std::runtime_error("File Not Found : " + VideoFile);
  }
  /*
     try {
     std::string win("default Name");
     cv::Mat im;
     if (GetImage(im)) {
     ShowImage(win, im);
     }
     }
     catch (const std::exception& e) {
     std::cerr << e.what() << "\n";
     }*/
}

CaptureVideo::~CaptureVideo()
{
  //std::cout << "Done destroying windows\n";
}

bool CaptureVideo::GetImage(cv::Mat &im)
{
  if (VidCapture.get()) {
    *VidCapture.get() >> im;
    //std::cout << "Got GetImage\n";
    if (im.empty()){
      //std::cout << "Got GetImage exception\n";
      throw std::runtime_error("Frame is empty..");
    }
    return true;
  }
  return false;
}

bool CaptureVideo::ShowImage(const std::string &windowName, const cv::Mat &img)
{
  //cv::namedWindow(windowName.c_str(), CV_WINDOW_NORMAL);
  cv::imshow(windowName.c_str(), img);
  //std::cout << "Show img\n";
  int k = cv::waitKey(30);
  // Quit when Esc is pressed
  if (k == 27) {
    std::cout << "ShowImage escape\n";
    return false;
  }
  return true;
}
#if 1
bool CaptureVideo::Run()
{
  int count(0);
  std::string windowName("Video Playback");
  DlibHandler dlibHandler("dummy_sessId", ShapePredictFile, FaceRecRsNetFile, LabelFile, FaceDescriptorFile);
  while(true) {
    try {
      count++;
      cv::Mat im;
      if (!GetImage(im)) {
        //std::cout << "img is empty\n";
        return false;
      }
      //std::cout << "Got Img count = " << count << "\n";
      if (count % SkipFrame == 0) {
        // std::cout << "Show img count xskipFrame\n";
        dlibHandler.ProcessData(im);
        if (!ShowImage(windowName, im)) {
          //std::cout << "Escape key recognized\n";
          cv::destroyAllWindows();
          return true;
        }
      }
    }
    catch (const std::exception& e) {
      std::cerr << e.what() << "\n";
      return false;
    }
  }
  return true;
}
#endif

bool CaptureVideo::Run(std::string &newVidLink, std::string sessId="1234")
{
  int count(0);
  auto ptr = std::make_unique<cv::VideoCapture>(newVidLink);
  VidCapture.reset(ptr.get());
  // TODO: Reset the DlibHandler to recognize new faces identified.
  //std::string windowName(newVidLink); // Remove after initial testing.
  std::cout << "Video Link = " << newVidLink.c_str() << "\n";
  DlibHandler dlibHandler(sessId, ShapePredictFile, FaceRecRsNetFile, LabelFile, FaceDescriptorFile);
  while(true) {
    try {
      count++;
      cv::Mat im;
      if (!GetImage(im)) {
        std::cerr << "img is empty\n";
        return false;
      }
      //std::cout << "Got Img count = " << count << "\n";
      if (count % SkipFrame == 0) {
        dlibHandler.ProcessData(im);
         //std::cout << "Show img count skipFrame\n";
        /*if (!ShowImage(windowName, im)) {
          //std::cout << "Escape key recognized\n";
          cv::destroyAllWindows();
          return true;
        } // Remove after intial testing.
        */
      }
    }
    catch (const std::exception& e) {
      std::cerr << e.what() << "\n";
      return false;
    }
  }
  return true;
}
