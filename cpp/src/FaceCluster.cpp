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
#include <stdlib.h>
#include <signal.h>

#include "FaceCluster.hpp"

FaceCluster::FaceCluster(const std::string &configFile):
  Parser(std::make_unique<JsonFileParser>(configFile)),
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

bool FaceCluster::Run(std::string &sessId)
{
//  sessId = "CS5zfGQnEn7147P7";
  SessionId = sessId;
  std::string clusterPath(StoragePath + sessId + "/cluster/");
  std::string landMarksPath(StoragePath + sessId + "/1/landmarks/");
  std::string alignedImgPath(StoragePath + sessId + "/1/30/");
  std::string cmd("mkdir -p " + clusterPath + " " + landMarksPath + " " + alignedImgPath);
  std::cout << "Executing command : " << cmd.c_str() << "\n";
  int ret = system(cmd.c_str());
  if (WIFSIGNALED(ret)
    && (WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT)) {
    std::cerr << "ERROR: Failed to execute command " << cmd.c_str() << "\n";
  }
  //  align/rotating the images as required to get best results for clustering.
  //  TODO: do a cpp version of faceAlignment.
  cmd = "python /opt/spookfish/scripts/faceAlign.py -p " + StoragePath + sessId + "/1/";
  std::cout << "Executing command : " << cmd.c_str() << "\n";
  ret = system(cmd.c_str());
  if (WIFSIGNALED(ret)
    && (WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT)) {
    std::cerr << "ERROR: Failed to execute command " << cmd.c_str() << "\n";
    return false;
  }
  std::cout << "Done executing Alignment script\n";
  cmd = "ls -d " + StoragePath + sessId + "/1/30/*.jpg >> " + clusterPath + ImageListFileName;
  ImageListFileName = clusterPath + ImageListFileName;
  std::cout << "Executing command : " << cmd.c_str() << "\n";
  ret = system(cmd.c_str());
  if (WIFSIGNALED(ret)
    && (WTERMSIG(ret) == SIGINT || WTERMSIG(ret) == SIGQUIT)) {
    std::cerr << "ERROR: Failed to execute command " << cmd.c_str() << "\n";
  }

  if (GetAllFaces()) {
    TFaceCluster cluster = IdentifyAllFaces();
    if (StorageEnabled.compare("true") == 0) {
      if (cluster.size() > 0) {
        Save(cluster, clusterPath);
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
  std::cout << "GetAllFacess returning false\n";
  return false;
}


bool FaceCluster::Run()
{
  if (GetAllFaces()) {
    TFaceCluster cluster = IdentifyAllFaces();
    if (StorageEnabled.compare("true") == 0) {
      if (cluster.size() > 0) {
        std::string dummyPaht("/tmp");
        Save(cluster, dummyPaht);
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

void FaceCluster::Save(TFaceCluster &cluster, std::string &path)
{
  if (StoragePath.compare("/tmp") == 0) {
    std::cerr << "WARNING: Storing in default path : " << StoragePath.c_str() << "\n";
  }
  unsigned long i(0);
  for(auto &v: cluster) {
    std::string file(path +"cluster_"+std::to_string(i)+".jpg");
    std::cout << "DEBUG: Storing cluster : " << file.c_str() << "\n";
    dlib::save_jpeg(dlib::tile_images(v),file.c_str());
    auto itr = LabelFileNameMap.find(i);
    if (itr != LabelFileNameMap.end()) {
      if (itr->second.size() == 1) {
        ImageAnchorLinkMap.erase(file);
      }
      else {
        int val =  itr->second.size();
        ImageAnchorLinkMap[file] = itr->second[val/2];
      }
    }
    std::string personName("cluster_" + std::to_string(i));
    ClusterStats.PersonNameVec.push_back(personName);
    // KSS
    /*
       dlib::array2d<rgb_pixel> loadedImg;
       dlib::load_image(loadedImg, file.c_str());
       dlib::array2d<rgb_pixel> sizeImg(200, 200);
       dlib::resize_image(loadedImg, sizeImg);
    //dlib::resize_image(loadedImg, sizeImg, dlib::interpolate_billinear());
    std::string newFile(path +"cluster_"+ "_resize_" + std::to_string(i)+".jpg");
    dlib::save_jpeg(loadedImg,newFile.c_str());
    //dlib::save_jpeg(loadedImg,file.c_str());
    */
    i++;
  }
  StoreFiles();
  std::string file = path + "Done.txt";
  std::cout << "Done. writing to file : " << file.c_str() << "\n";
  std::ofstream out(file);
  out << "Done\n";
  out.close();
  int pos = path.find_last_of("/");
  std::string statsFile(path.substr(0,pos));
  pos = statsFile.find_last_of("/");
  statsFile = statsFile.substr(0,pos) + "/Stats.txt";
  SaveStats(statsFile);
}

bool FaceCluster::CheckFileExists(std::string &file)
{
  struct stat buffer;
  bool val(false);
  if ((stat(file.c_str(), &buffer) == 0)) {
    val = true;
    std::cout << "File " << file.c_str() << " Found.\n";
  }
  else {
    std::cout << "File " << file.c_str() << " Not Found.\n";
  }
  return val;
}


bool FaceCluster::SaveStats(std::string &file)
{
  std::string lines("");
  bool retVal(true);
  if (ClusterStats.TotalClusters > 0) {
    if (CheckFileExists(file)) {
      std::ifstream infile(file);
      std::string line("");
      while (std::getline(infile, line)) {
        lines += line + "\n";
      }
    }
    lines += "Total Person identified \t:\t" + std::to_string(ClusterStats.TotalClusters) + "\n";
    int i(0);
    for(auto &v: ClusterStats.PersonNameVec) {
      lines += v + "\t:\t" + std::to_string(ClusterStats.TotalFacesInEachCluster[i]) +"\n";
    }
    std::cout << "Storing Stats file : " << file.c_str() << "\n";
    std::ofstream out(file);
    out << lines;
    out.close();
  }
  else {
    std::cout << "No faces identified in this video\n";
    retVal = false;
  }
  return retVal;
}

bool FaceCluster::StoreFiles()
{
  std::string file(StoragePath + SessionId + "/clusterImagesAnchor.txt");
  std::string lines("");
  for(auto &itr: ImageAnchorLinkMap) {
    lines += itr.second+ "\t" + itr.first+ "\n";
  }
  std::cout << "StoreFiles() writing to file : " << file.c_str() << "\n";
  std::ofstream out(file);
  out << lines;
  out.close();
  return true;
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
      ImageFiles.push_back(line);
    }
  }
/*  for(auto &v:ImageFiles) {
    std::cout << "KSS Img file = " << v << "\n";
  }*/
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
      if (length(faceDescriptors[i]-faceDescriptors[j]) < 0.6) {
        edges.push_back(sample_pair(i,j));
      }
    }
  }
  std::vector<unsigned long> labels;
  const auto numClusters = dlib::chinese_whispers(edges, labels);
  std::cout << "number of person found in the images: "<< numClusters << "\n";
  ClusterStats.TotalClusters = numClusters;

  for (unsigned long i = 0 ; i < labels.size(); i++) {
    auto itr = LabelFileNameMap.find(labels[i]);
    if (itr == LabelFileNameMap.end()) {
      std::vector<std::string> tmp;
      tmp.push_back(ImageFiles[i]);
      LabelFileNameMap[labels[i]] = tmp;
    }
    else {
      itr->second.push_back(ImageFiles[i]);
    }
    //std::cout << "LabelFileNameMap itr->second.size() = " << itr->second.size() << "\n";
  }

  TFaceCluster cluster;
  for (size_t cluster_id = 0; cluster_id < numClusters; ++cluster_id) {
    std::vector<dlib::matrix<dlib::rgb_pixel>> temp;
    for (size_t j = 0; j < labels.size(); ++j) {
      if (cluster_id == labels[j]) {
        temp.push_back(FaceVector[j]);
        /*std::string file("/tmp/images/sant_"+std::to_string(j)+".jpg");
        std::cout << "CLUSTER IMG: " << file.c_str() << "\n";
        save_jpeg(FaceVector[j], file.c_str());*/
      }
    }
    std::cout << "KSS total faces in a cluster = "  << temp.size() << "\n";
    if (temp.size() > 1) {
      ClusterStats.TotalFacesInEachCluster.push_back(temp.size());
    }
    //std::string file("sant_" + to_string(cluster_id)+ ".jpg");
    //save_jpeg(tile_images(temp),file.c_str());
    //std::cout << "DEBUG: Dominance value = " <<  temp.size() << "\n";
    cluster.push_back(temp);
  }
#if 0
  for(auto &mapItr : LabelFileNameMap) {
    std::cout << "LABLE = " << mapItr.first;
    for(auto &v : mapItr.second) {
      std::cout << " FILE = " << v << " ";
    }
    std::cout << "\n";
  }
#endif
  return cluster;
}
