#include <iostream>

#include "DlibHandler.hpp"
#include <opencv2/imgproc/imgproc.hpp>

//DlibHandler::DlibHandler(cv::Mat imgBgr):
DlibHandler::DlibHandler(std::string &shapePredictFile, std::string &faceRecRsNetFile):
  TotalFacesInImage(0),
  Shape(),
  FaceDetector(dlib::get_frontal_face_detector())
{
  //FaceDetector = dlib::get_frontal_face_detector();
  dlib::deserialize(shapePredictFile) >> LandMarkDetector;
  dlib::deserialize(faceRecRsNetFile) >> AnetType;
}

DlibHandler ::~DlibHandler()
{
  // Empty.
}

void DlibHandler::ProcessImage()
{
  cv::cvtColor(BgrImage, RgbImage, cv::COLOR_BGR2RGB);
  DlibImageMat = dlib::mat(dlib::cv_image<dlib::rgb_pixel>(RgbImage));
}

void DlibHandler::FaceDetection()
{
  FaceRectangles = FaceDetector(DlibImageMat);
  TotalFacesInImage = FaceRectangles.size();
  std::cout << "Total faces = " << TotalFacesInImage << "\n";
}

void DlibHandler::LandmarkDetector()
{
  for(auto &v:FaceRectangles) {
    dlib::full_object_detection landMark = LandMarkDetector(DlibImageMat, v);
    LandMarks.push_back(landMark);
    dlib::matrix<dlib::rgb_pixel> faceChip;
    dlib::extract_image_chip(DlibImageMat, dlib::get_face_chip_details(landMark,150,0.25), faceChip);
    FaceChips.push_back(faceChip);
    dlib::matrix<float,0,1> faceDescritionQry = AnetType(faceChip);
  }
}

void DlibHandler::DrawShapes(cv::Mat &img)
{
  Shape.BoundinBox(img, FaceRectangles);
  Shape.Circle(img, FaceRectangles);
}

void DlibHandler::ProcessData(cv::Mat &img)
{
  BgrImage = img.clone();
  RgbImage = img.clone();
  ProcessImage();
  FaceDetection();
  LandmarkDetector();
  DrawShapes(img);
  return;
}
