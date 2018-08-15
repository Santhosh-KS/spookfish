#ifndef CAPTURE_VIDEO_HPP
#define CAPTURE_VIDEO_HPP

#include <string>
#include <memory>
#include "NotCopyable.hpp"

#include <opencv2/highgui.hpp>

class CaptureVideo: public NotCopyable
{
 private:
   std::string VideoFile;
   uint16_t SkipFrame;
   std::unique_ptr<cv::VideoCapture>  VidCapture;

   CaptureVideo() = delete;
   bool GetImage(cv::Mat &im);
   bool ShowImage(const std::string &windowName, cv::Mat &img);
 public:
   explicit CaptureVideo(std::string file, uint16_t skipFrame);
   ~CaptureVideo();
   bool Run();
};

#endif // CAPTURE_VIDEO_HPP
