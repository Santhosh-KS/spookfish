#ifndef DLIB_HANDLER_HPP
#define DLIB_HANDLER_HPP

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

#include <vector>
#include <map>

#include <dlib/string.h>
#include <dlib/dnn.h>
#include <dlib/image_io.h>
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>

#include "NotCopyable.hpp"
#include "RsNetDlib.hpp"
#include "DrawingUtils.hpp"

class DlibHandler : public NotCopyable
{
  private:
    std::string SessionId;
    std::string ImgStoragePath;
    cv::Mat RgbImage;
    cv::Mat BgrImage;
    uint16_t TotalFacesInImage;
    DrawingUtils Shape;
    dlib::frontal_face_detector FaceDetector;
    dlib::shape_predictor LandMarkDetector;
    anet_type AnetType;
    dlib::matrix<dlib::rgb_pixel> DlibImageMat;
    std::vector<dlib::rectangle> FaceRectangles;
    std::vector<dlib::full_object_detection>  LandMarks;
    //std::vector<dlib::matrix<rgb_pixel>> FaceChips;
    std::vector<dlib::matrix<float,0,1>> FaceDescriptionQuerys;
    std::vector<int> TaggedFaceVector;
    std::vector<std::string> CurrentFaceLabelVec;
    std::map<int,std::string> IdPersonMap;
    std::map<std::string,int> FaceDescriptorIdMap;

    struct ImageStats {
      ImageStats(): TotalImages(0),
      TotalZoomShots(0),
      TotalFaceRecognizedImages(0),
      TotalImagesWithOneFace(0),
      TotalImagesWithTwoFace(0),
      TotalImagesWithThreeFace(0),
      TotalImagesWithFourFace(0),
      TotalImagesWithFiveFace(0),
      TotalImagesWithSixOrMoreFace(0)
      {
        //Empty
      }
      uint64_t TotalImages;
      uint64_t TotalZoomShots;
      uint64_t TotalFaceRecognizedImages;
      uint64_t TotalImagesWithOneFace;
      uint64_t TotalImagesWithTwoFace;
      uint64_t TotalImagesWithThreeFace;
      uint64_t TotalImagesWithFourFace;
      uint64_t TotalImagesWithFiveFace;
      uint64_t TotalImagesWithSixOrMoreFace;
    };

    struct ImageStats ImgStats;

    DlibHandler() = delete;
    void ProcessImage();
    void FaceDetection();
    void FaceLandMarkDetector(std::string &timeStamp);
    void DrawShapes(const cv::Mat &);
    void CreateFaceDescriptorIdMap(const std::string &file);
    void CreateIdPersonMap(const std::string &file);
    void SaveImage(const cv::Mat &im, const std::string &path, std::string &timeStamp);
    int FindMatchingFace(dlib::matrix<float,0,1> &fDesqry);
    std::string GetEpcohTime();
    void PrintStats();
  public:
    DlibHandler(std::string sessId, std::string &shapePredictFile,
        std::string &faceRecRsNetFile, std::string &personFile, std::string &faceDescFile);
    ~DlibHandler();
    void ProcessData(const cv::Mat &);
    void Retrain(std::string &shapePredictFile,
        std::string &faceRecRsNetFile, std::string &personIdFile,
        std::string &faceDescriptorFile);
};

#endif // DLIB_HANDLER_HPP
