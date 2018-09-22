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
#include <fstream>
#include <sys/stat.h>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <dlib/string.h>
#include <dlib/dnn.h>
#include <dlib/image_io.h>
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>


#include "Enroll.hpp"
#include "RsNetDlib.hpp"

bool Enroll::CheckFileExists(std::string &file)
{
  struct stat buffer;
  bool val(false);
  if ((stat(file.c_str(), &buffer) == 0)) {
    val = true;
    std::cout << "File " << file.c_str() << "\n";
  }
  else {
    std::cout << "File " << file.c_str() << "Not found..\n";
  }
  return val;
}

std::vector<std::string> Enroll::ReadFile(std::string &file)
{
  std::ifstream infile(file);
  std::string line;
  std::vector<std::string> vec;
  int index(0);
  while (std::getline(infile, line)) {
    if (line.empty()) {
      continue;
    }
    else {
      ImageFilesVec.push_back(line);
      LablesVec.push_back(index);
      index++;
    }
  }
  return vec;
}

Enroll::Enroll(std::string &facesFile, std::string &lableFile):
  FacesFile(facesFile),
  LableFile(lableFile),
  SessionId("12345"),
  ReadyToEnroll(false)
{
  if (CheckFileExists(facesFile) &&   CheckFileExists(lableFile)) {
    ImageFilesVec = ReadFile(FacesFile);
    if (ImageFilesVec.empty() || LablesVec.empty()) {
      ReadyToEnroll = false;
    }
    else {
      ReadyToEnroll = true;
    }
  }
}

Enroll::~Enroll()
{
  // Empty
}

bool Enroll::Run(std::string &sessId)
{
  if (ReadyToEnroll) {
    cv::String predictorPath;
    cv::String faceRecognitionModelPath;
    predictorPath = "/opt/spookfish/shape_predictor_68_face_landmarks.dat";
    faceRecognitionModelPath = "/opt/spookfish/dlib_face_recognition_resnet_model_v1.dat";

    dlib::frontal_face_detector faceDetector = dlib::get_frontal_face_detector();
    dlib::shape_predictor landmarkDetector;
    dlib::deserialize(predictorPath) >> landmarkDetector;
    anet_type net;
    dlib::deserialize(faceRecognitionModelPath) >> net;

    std::vector<dlib::matrix<float,0,1>> faceDescriptors;
    std::vector<int> faceLabels;

    for(int i=0; i < ImageFilesVec.size(); i++) {
      std::string imgFile = ImageFilesVec[i];
      int imgLabel = LablesVec[i];
      std::cout << "processing: " << imgFile.c_str() << "\n";
      std::cout << "imageLabel : " << imgLabel << "\n";
      cv::Mat im = cv::imread(imgFile, cv::IMREAD_COLOR);
      cv::Mat imRGB;
      cv::cvtColor(im, imRGB, cv::COLOR_BGR2RGB);
       dlib::matrix<dlib::rgb_pixel> imDlib(dlib::mat(dlib::cv_image<dlib::rgb_pixel>(imRGB)));
       std::vector<dlib::rectangle> faceRects = faceDetector(imDlib);
       for (int j = 0; j < faceRects.size(); j++) {
         dlib::full_object_detection landmarks = landmarkDetector(imDlib, faceRects[j]);
         dlib::matrix<rgb_pixel> face_chip;
         dlib::extract_image_chip(imDlib, dlib::get_face_chip_details(landmarks, 150, 0.25), face_chip);
         matrix<float,0,1> faceDescriptor = net(face_chip);
         faceDescriptors.push_back(faceDescriptor);
         faceLabels.push_back(imgLabel);
       }
    }
    std::cout << "number of face descriptors " << faceDescriptors.size() << "\n";
    std::cout << "number of face labels " << faceLabels.size() << "\n";
    int pos = LableFile.find_last_of("/");
    const std::string descriptorsPath = LableFile.substr(0,pos) + "/descriptors.csv";
    std::ofstream ofs;
    ofs.open(descriptorsPath);
    for (int m = 0; m < faceDescriptors.size(); m++) {
      dlib::matrix<float,0,1> faceDescriptor = faceDescriptors[m];
      std::vector<float> faceDescriptorVec(faceDescriptor.begin(), faceDescriptor.end());
      ofs << faceLabels[m];
      ofs << ";";
      for (int n = 0; n < faceDescriptorVec.size(); n++) {
        ofs << std::fixed << std::setprecision(8) << faceDescriptorVec[n];
        if ( n == (faceDescriptorVec.size() - 1)) {
           ofs << "\n";
        }
        else {
          ofs << ";";  // add newline character if last element of descriptor
        }
      }
    }
    ofs.close();
  }
  else {
    return false;
  }
  return true;
}


