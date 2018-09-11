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

#include <fstream>

#include "FaceCluster.hpp"

FaceCluster::FaceCluster(const std::string &configFile):
  Parser(new JsonFileParser(configFile)),
  ImageListFileName(Parser->Value("ImageListFileName")),
  StoragePath(Parser->Value("StoragePath")),
  ModelFile(Parser->Value("ModelFile")),
  RsNetFile(Parser->Value("RsNetFile")),
  StorageEnabled(Parser->Value("StorageEnabled")),
  Detector(dlib::get_frontal_face_detector())
{
  try {
    deserialize(ModelFile) >> ShapePredictor;
    deserialize(RsNetFile) >> AnetType;
  }
  catch(...) {
    std::cerr << "ERROR: Couldn't find Model: " << ModelFile.c_str();
    std::cerr << "ERROR: Couldn't find rsNet: " << RsNetFile.c_str();
    assert(0);
  }
}

FaceCluster::~FaceCluster()
{
  // Empty.
}

bool FaceCluster::Run()
{
  if (GetAllFaces()) {
    TFaceCluster cluster = IdentifyAllFaces();
    if (StorageEnabled.compare("true") == 0) {
      if (cluster.size() > 0) {
        Save(cluster);
        return true;
      }
      else {
        std::cout << "ERROR: Images doesn't contain any Faces.\n";
        return false;
      }
    }
    std::cout << "NOTE: Storage is disabled for the cluster\n";
    return true;
  }
  return false;
}

void FaceCluster::Save(TFaceCluster &cluster)
{
  if (StoragePath.compare("/tmp") == 0) {
    std::cerr << "WARNING: Storing in default path : " << StoragePath.c_str() << "\n";
  }
  int i(0);
  for(auto &v: cluster) {
    std::string file(StoragePath +"/cluster_"+std::to_string(i)+".jpg");
    std::cout << "DEBUG: Storing cluster : " << file.c_str() << "\n";
    dlib::save_jpeg(dlib::tile_images(v),file.c_str());
    i++;
  }
}

bool FaceCluster::GetAllFaces()
{
  std::ifstream infile(ImageListFileName);
  std::string line;
  dlib::matrix<dlib::rgb_pixel> img;
  std::cout << "DEBUG: Reading file : " << ImageListFileName.c_str() << "\n";
  while (std::getline(infile, line)) {
    dlib::load_image(img, line);
    std::cout << "DEBUG: Processing file : " << line.c_str() << "\n";
    for (auto face : Detector(img)) {
      auto shape = ShapePredictor(img, face);
      dlib::matrix<dlib::rgb_pixel> face_chip;
      dlib::extract_image_chip(img, dlib::get_face_chip_details(shape,150,0.25), face_chip);
      FaceVector.push_back(std::move(face_chip));
    }
  }
  if (FaceVector.size() == 0) {
    std::cerr << "No faces found in images in file: " << ImageListFileName.c_str();
    return false;
  }
  else {
    return true;
  }
}

FaceCluster::TFaceCluster FaceCluster::IdentifyAllFaces()
{
  std::cout << "DEBUG: Identifying faces...\n";
  std::vector<dlib::matrix<float,0,1>> faceDescriptors = AnetType(FaceVector);
  std::vector<dlib::sample_pair> edges;
  for (size_t i = 0; i < faceDescriptors.size(); ++i) {
    for (size_t j = i+1; j < faceDescriptors.size(); ++j) {
      if (length(faceDescriptors[i]-faceDescriptors[j]) < 0.5) {
        edges.push_back(sample_pair(i,j));
      }
    }
  }
  std::vector<unsigned long> labels;
  const auto numClusters = dlib::chinese_whispers(edges, labels);
  std::cout << "number of people found in the image: "<< numClusters << "\n";
  TFaceCluster cluster;
  for (size_t cluster_id = 0; cluster_id < numClusters; ++cluster_id) {
    std::vector<dlib::matrix<dlib::rgb_pixel>> temp;
    for (size_t j = 0; j < labels.size(); ++j) {
      if (cluster_id == labels[j]) {
        temp.push_back(FaceVector[j]);
        //save_jpeg(FaceVector[j], file.c_str());
      }
    }
    //std::string file("sant_" + to_string(cluster_id)+ ".jpg");
    //save_jpeg(tile_images(temp),file.c_str());
    //std::cout << "DEBUG: Dominance value = " <<  temp.size() << "\n";
    cluster.push_back(temp);
  }
  return cluster;
}
