#include <iostream>

#include "DlibHandler.hpp"
#include <opencv2/imgproc/imgproc.hpp>

//DlibHandler::DlibHandler(cv::Mat imgBgr):
DlibHandler::DlibHandler(std::string &shapePredictFile, std::string &faceRecRsNetFile,
    std::string &personIdFile, std::string &faceDescriptorFile):
  TotalFacesInImage(0),
  Shape(),
  CurrentFaceLabel("Unknown"),
  FaceDetector(dlib::get_frontal_face_detector())
{
  Retrain(shapePredictFile, faceRecRsNetFile, personIdFile, faceDescriptorFile);
}

DlibHandler ::~DlibHandler()
{
  // Empty.
}

void DlibHandler::ProcessImage()
{
  //cv::cvtColor(BgrImage, RgbImage, cv::COLOR_BGR2RGB);
  DlibImageMat = dlib::mat(dlib::cv_image<dlib::rgb_pixel>(RgbImage));
}

void DlibHandler::FaceDetection()
{
  FaceRectangles = FaceDetector(DlibImageMat);
  TotalFacesInImage = FaceRectangles.size();
  //std::cout << "Total faces = " << TotalFacesInImage << "\n";
}

void DlibHandler::FaceLandMarkDetector()
{
  for(auto &v:FaceRectangles) {
    dlib::full_object_detection landMark = LandMarkDetector(DlibImageMat, v);
    LandMarks.push_back(landMark);
    dlib::matrix<dlib::rgb_pixel> faceChip;
    dlib::extract_image_chip(DlibImageMat, dlib::get_face_chip_details(landMark,150,0.25), faceChip);
    //FaceChips.push_back(faceChip);
    dlib::matrix<float,0,1> faceDescritionQry = AnetType(faceChip);
    FindMatchingFace(faceDescritionQry);
  }
}

void DlibHandler::FindMatchingFace(dlib::matrix<float,0,1> &fDesqry)
{
  //CurrentFaceLabelVec.clear();
  for(auto i = 0; i < FaceDescriptionQuerys.size(); ++i) {
    auto distance = dlib::length(FaceDescriptionQuerys[i] - fDesqry);
    if (distance < 0.6) {
      auto itr = IdPersonMap.find(i);
      if ( itr != IdPersonMap.end()) {
        //CurrentFaceLabelVec.push_back(itr->second);
        CurrentFaceLabel = itr->second;
      }
    }
  }
}

void DlibHandler::DrawShapes(cv::Mat &img)
{
  Shape.BoundinBox(img, FaceRectangles, CurrentFaceLabel);
  Shape.Circle(img, FaceRectangles);
}

void DlibHandler::ProcessData(cv::Mat &img)
{
  BgrImage = img.clone();
  RgbImage = img.clone();
  ProcessImage();
  FaceDetection();
  if (TotalFacesInImage > 0) {
    FaceLandMarkDetector();
    DrawShapes(img);
  }
  return;
}

void DlibHandler::CreateIdPersonMap(std::string &file)
{
  std::ifstream ifs(file);
  std::string line("");

  while (std::getline(ifs, line)) {
    try {
      std::istringstream iss(line);
      auto const pos = line.find_last_of(';');
      auto id = line.substr(pos+1);
      auto name = line.substr(0,pos);
      std::cout << "id = " << id.c_str() << " name = " << name.c_str() << "\n";
      IdPersonMap.insert(std::pair<int,std::string>(std::stoi(id), name));
    }
    catch (const std::exception& e) {
      std::cerr << e.what() << "\n";
    }
  }
}

void DlibHandler::CreateFaceDescriptorIdMap(std::string &file)
{
  std::ifstream ifs(file);
  std::string line("");

  while (std::getline(ifs, line)) {
    try {
      std::istringstream iss(line);
      auto const pos = line.find_first_of(';');
      std::string id = line.substr(0,pos);
      auto faceDescriptor = line.substr(pos+1);
      std::cout << "id = " << id.c_str() << " fd = " << faceDescriptor.c_str() << "\n";
      FaceDescriptorIdMap.insert(std::pair<std::string, int>(faceDescriptor, std::stoi(id)));
    }
    catch (const std::exception& e) {
      std::cerr << e.what() << "\n";
    }
  }
}

void DlibHandler::Retrain(std::string &shapePredictFile, std::string &faceRecRsNetFile,
    std::string &personIdFile, std::string &faceDescriptorFile)
{
  dlib::deserialize(shapePredictFile) >> LandMarkDetector;
  dlib::deserialize(faceRecRsNetFile) >> AnetType;
  CreateIdPersonMap(personIdFile);
  CreateFaceDescriptorIdMap(faceDescriptorFile);
}
