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
#include <limits>
#include <ctime>
#include <chrono>
#include <stdlib.h>
#include <signal.h>

#include "DlibHandler.hpp"
#include <opencv2/imgproc/imgproc.hpp>

DlibHandler::DlibHandler(std::string sessId, std::string &shapePredictFile, std::string &faceRecRsNetFile,
    std::string &personIdFile, std::string &faceDescriptorFile):
  SessionId(sessId),
  ImgStoragePath("/tmp/images/" + SessionId),
  TotalFacesInImage(0),
  Shape(),
  FaceDetector(dlib::get_frontal_face_detector())
{
  CurrentFaceLabelVec.clear();
  Retrain(shapePredictFile, faceRecRsNetFile, personIdFile, faceDescriptorFile);
  for(int i = 1; i < 6; i++) {
    std::string cmd("mkdir -p " + ImgStoragePath + "/" + std::to_string(i));
    std::cout << "Creating New DIR : " << cmd.c_str() << "\n";
    int ret = system(cmd.c_str());
    if (WIFSIGNALED(ret)
        && (WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT)) {
      std::cerr << "ERROR: Failed to execute command " << cmd.c_str() << "\n";
    }
  }
  std::string cmd("mkdir -p " + ImgStoragePath + "/6_plus/");
  int ret = system(cmd.c_str());
  if (WIFSIGNALED(ret)
      && (WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT)) {
    std::cerr << "ERROR: Failed to execute command " << cmd.c_str() << "\n";
  }
  cmd = "mkdir -p " + ImgStoragePath + "/zoom_shot";
  ret = system(cmd.c_str());
  if (WIFSIGNALED(ret)
      && (WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT)) {
    std::cerr << "ERROR: Failed to execute command " << cmd.c_str() << "\n";
  }
}

DlibHandler ::~DlibHandler()
{
  PrintStats();
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
  //std::cout << "Total faces = " << TotalFacesInImage << "\n";
}

void DlibHandler::FaceLandMarkDetector(std::string &timeStamp)
{
  CurrentFaceLabelVec.clear();
  for(auto &v:FaceRectangles) {
    dlib::full_object_detection landMark = LandMarkDetector(DlibImageMat, v);
    LandMarks.push_back(landMark);
    dlib::matrix<dlib::rgb_pixel> faceChip;
    dlib::extract_image_chip(DlibImageMat, dlib::get_face_chip_details(landMark,150,0.25), faceChip);
    if (v.area() >= 20000)  {
      ImgStats.TotalZoomShots++;
    }
#if 1
    // Store the zoomed image.
    if (v.area() >= 40000) {
      // TODO: Only when emotion recoginition is done, then it is useful to store the zoomed image.
      std::string strPath(ImgStoragePath +"/zoom_shot/");
      strPath = strPath + timeStamp + ".jpg";
      std::cout << "Saving image in path : " << strPath.c_str() << "\n";
      dlib::save_jpeg(faceChip, strPath.c_str());
    }
#endif
    //FaceChips.push_back(faceChip);

    dlib::matrix<float,0,1> faceDescritionQry = AnetType(faceChip);
    auto match = FindMatchingFace(faceDescritionQry);

    auto itr = IdPersonMap.find(match);
    if ( itr != IdPersonMap.end()) {
      std::cout << itr->second << "\n";
      CurrentFaceLabelVec.push_back(itr->second);
    }
    else {
      CurrentFaceLabelVec.push_back("Unknown");
    }
  }
}

int DlibHandler::FindMatchingFace(dlib::matrix<float,0,1> &fDesqry)
{
  auto match(std::numeric_limits<int>::max());
  for(auto i = 0; i < FaceDescriptionQuerys.size(); ++i) {
    auto distance = dlib::length(FaceDescriptionQuerys[i] - fDesqry);
    //std::cout << "distance  = " << distance << "\n";
    if (distance < 0.5) {
      match = std::min(match, TaggedFaceVector[i]);
      //std::cout << "Valid distance  = " << distance << " match = " << match << "\n";
    }
  }
  return match;
}

void DlibHandler::DrawShapes(const cv::Mat &img)
{
  Shape.BoundinBox(img, FaceRectangles, CurrentFaceLabelVec);
  Shape.Circle(img, FaceRectangles);
}

void DlibHandler::ProcessData(const cv::Mat &img)
{
  BgrImage = img.clone();
  RgbImage = img.clone();
  ProcessImage();
  FaceDetection();
  ImgStats.TotalImages++;
  if (TotalFacesInImage > 0) {
    std::string timeStamp(GetEpcohTime());
    FaceLandMarkDetector(timeStamp);
    std::string path = ImgStoragePath;
    // Get the images captured stats.
    ImgStats.TotalFaceRecognizedImages++;
    if (TotalFacesInImage < 6) {
      path += "/"+std::to_string(TotalFacesInImage)+"/";
      switch(TotalFacesInImage) {
        case 1:
          ImgStats.TotalImagesWithOneFace++;
          break;
        case 2:
          ImgStats.TotalImagesWithTwoFace++;
          break;
        case 3:
          ImgStats.TotalImagesWithThreeFace++;
          break;
        case 4:
          ImgStats.TotalImagesWithFourFace++;
          break;
        case 5:
          ImgStats.TotalImagesWithFiveFace++;
          break;
      }
    }
    else {
      path += "/6_plus/";
      ImgStats.TotalImagesWithSixOrMoreFace++;
    }
    // Enable only when required. Hogs Disk space.
    // TODO: Make it configurable.
    SaveImage(img, path, timeStamp);
    //DrawShapes(img);
  }
  return;
}

void DlibHandler::CreateIdPersonMap(const std::string &file)
{
  std::ifstream ifs(file);
  std::string line("");

  IdPersonMap.clear();
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
      break;
    }
  }
}

void DlibHandler::CreateFaceDescriptorIdMap(const std::string &file)
{
  std::ifstream ifs(file);
  std::string line("");

  FaceDescriptorIdMap.clear();
  TaggedFaceVector.clear();
  while (std::getline(ifs, line)) {
    try {
      std::istringstream iss(line);
      auto const pos = line.find_first_of(';');
      std::string id = line.substr(0,pos);
      auto faceDescriptor = line.substr(pos+1);
      //std::cout << "id = " << id.c_str() << " fd = " << faceDescriptor.c_str() << "\n";
      FaceDescriptorIdMap.insert(std::pair<std::string, int>(faceDescriptor, std::stoi(id)));
    }
    catch (const std::exception& e) {
      std::cerr << e.what() << "\n";
      break;
    }
  }

  // Form a valid FaceDescriptionQuery from string.
  try {
    FaceDescriptionQuerys.clear();
    std::string valueStr;
    for(auto &itr: FaceDescriptorIdMap) {
      std::string str(itr.first);
      std::stringstream ss(str);
      std::vector<float> floatVec;
      TaggedFaceVector.push_back(itr.second);
      while (getline(ss, valueStr, ';')) {
        if (!valueStr.empty()) {
          floatVec.push_back(std::atof(valueStr.c_str()));
        }
      }
      dlib::matrix<float, 0, 1> faceDes = dlib::mat(floatVec);
      FaceDescriptionQuerys.push_back(std::move(faceDes));
    }
    //std::cout << "FaceDescriptionQuerys.size() = " << FaceDescriptionQuerys.size() << "\n";
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return;
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

std::string DlibHandler::GetEpcohTime()
{
  using namespace  std::chrono;
  milliseconds ms = duration_cast< milliseconds >
    (system_clock::now().time_since_epoch());
  return std::to_string(ms.count());
}

void DlibHandler::SaveImage(const cv::Mat &im, const std::string &path, std::string &timeStamp)
{
  //auto localTime(GetEpcohTime());
  std::string imgStorePath(path);
  std::string imgName(timeStamp);
  //imgStorePath += imgName + "_" + std::to_string(TotalFacesInImage) + ".jpg";
  imgStorePath += imgName + ".jpg";
  std::cout << "Saving Image in : " << imgStorePath.c_str() << "\n";
  cv::imwrite(imgStorePath, im);
}

void DlibHandler::PrintStats()
{
  std::cout << " Total Images = " << ImgStats.TotalImages << "\n";
  std::cout << " Total zoom/closeup shots = " << ImgStats.TotalZoomShots << "\n";
  std::cout << " Total Face Rec Images = " << ImgStats.TotalFaceRecognizedImages << "\n";
  std::cout << " Total 1 Face in image = " << ImgStats.TotalImagesWithOneFace << "\n";
  std::cout << " Total 2 Faces in image = " << ImgStats.TotalImagesWithTwoFace << "\n";
  std::cout << " Total 3 Faces in image = " << ImgStats.TotalImagesWithThreeFace << "\n";
  std::cout << " Total 4 Faces in image = " << ImgStats.TotalImagesWithFourFace << "\n";
  std::cout << " Total 5 Faces in image = " << ImgStats.TotalImagesWithFiveFace << "\n";
  std::cout << " Total 6 or more Faces in image = " << ImgStats.TotalImagesWithSixOrMoreFace << "\n";
}
