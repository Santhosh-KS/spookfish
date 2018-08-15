#include <iostream>
#include <stdexcept>

#include "CaptureVideo.hpp"
#include "DlibHandler.hpp"


CaptureVideo::CaptureVideo(std::string file, uint16_t skipFrame = 10):
  VideoFile(file),
  SkipFrame(skipFrame),
  VidCapture(new cv::VideoCapture(file))
{
  if (!VidCapture->isOpened()) {
    VidCapture.release();
    throw std::runtime_error("File Not Found : " + file);
  }
  try {
    std::string win("default Name");
    cv::Mat im;
    if (GetImage(im)) {
      ShowImage(win, im);
    }
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
  }
}

CaptureVideo::~CaptureVideo()
{
  cv::destroyAllWindows();
  //std::cout << "Done destryoing windows\n";
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

bool CaptureVideo::ShowImage(const std::string &windowName, cv::Mat &img)
{
  cv::imshow(windowName.c_str(), img);
  //std::cout << "Show img\n";
  int k = cv::waitKey(30);
  // Quit when Esc is pressed
  if (k == 27) {
    //std::cout << "ShowImage escape\n";
    return false;
  }
  return true;
}

bool CaptureVideo::Run()
{
  int count(0);
  std::string windowName("Video Playback");
  std::string shapePredictFile("/home/santhosh/course/final_project/cpp/data/shape_predictor_5_face_landmarks.dat");
  std::string faceRecRsNetFile("/home/santhosh/course/final_project/cpp/data/dlib_face_recognition_resnet_model_v1.dat");
  while(true) {
    try {
      count++;
      cv::Mat im;
      if (!GetImage(im)) {
        //std::cout << "img is null\n";
        return false;
      }
      //std::cout << "Got Img count = " << count << "\n";
      if (count % SkipFrame == 0) {
        // std::cout << "Show img count xskipFrame\n";
        DlibHandler handler(im, shapePredictFile, faceRecRsNetFile);
        if (!ShowImage(windowName, im)) {
          //std::cout << "Escape key recognized\n";
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
