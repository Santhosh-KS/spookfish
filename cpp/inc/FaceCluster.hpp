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

#ifndef FACE_CLUSTER_HPP
#define FACE_CLUSTER_HPP

#include <string>
#include <vector>
#include <memory>

#include <dlib/dnn.h>
//#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>

#include "NotCopyable.hpp"
#include "RsNetDlib.hpp"
#include "JsonFileParser.hpp"

class FaceCluster : public NotCopyable
{
  private:
    std::unique_ptr<JsonFileParser> Parser;
    std::string StoragePath;
    std::string ImageListFileName;
    std::string ModelFile;
    std::string RsNetFile;
    std::string StorageEnabled;
    dlib::frontal_face_detector Detector;
    dlib::shape_predictor ShapePredictor;
    anet_type AnetType;
    std::vector<dlib::matrix<dlib::rgb_pixel>> FaceVector;
    typedef std::vector<std::vector<dlib::matrix<dlib::rgb_pixel>>> TFaceCluster;

    FaceCluster() = delete;
    void Save(TFaceCluster &cluster);
    bool GetAllFaces();
    TFaceCluster IdentifyAllFaces();
  public:
    FaceCluster(const std::string &config);
    ~FaceCluster();
    bool Run();
};

#endif // FACE_CLUSTER_HPP
