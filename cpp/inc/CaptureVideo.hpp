#ifndef CAPTURE_VIDEO_HPP
#define CAPTURE_VIDEO_HPP

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

#include <string>
#include <memory>

#include "NotCopyable.hpp"
#include "JsonFileParser.hpp"

#include <opencv2/highgui.hpp>

class CaptureVideo: public NotCopyable
{
  private:
    std::unique_ptr<JsonFileParser> Parser;
    std::string VideoFile;
    std::string ShapePredictFile;
    std::string FaceRecRsNetFile;
    std::string LabelFile;
    std::string FaceDescriptorFile;

   uint64_t SkipFrame;
   std::unique_ptr<cv::VideoCapture>  VidCapture;

   CaptureVideo() = delete;
   bool GetImage(cv::Mat &im);
   bool ShowImage(const std::string &windowName, const cv::Mat &img);
 public:
   explicit CaptureVideo(const std::string &file);
   ~CaptureVideo();
   bool Run();
   bool Run(std::string &newVidLink, std::string sessId);
};

#endif // CAPTURE_VIDEO_HPP
