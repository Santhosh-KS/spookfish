// generic includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <map>
#include <ctime>
#include <chrono>
#include <iomanip> // setprecision
#include <sstream> // stringstream

// specific include
#include <dirent.h>

// opencv specific includes
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

// dlib specific includes
#include <dlib/string.h>
#include <dlib/dnn.h>
#include <dlib/image_io.h>
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>

#include "RsNetDlib.hpp"
#include "JsonParser.hpp"

#define SKIP_FRAMES 10
#define THRESHOLD 0.5

static void ReadLableNameMap(const std::string& filename, std::vector<std::string>& names, std::vector<int>& labels,
    std::map<int, std::string>& labelNameMap, char separator = ';')
{
  std::ifstream file(filename.c_str(), std::ifstream::in);
  if (!file) {
    std::string error_message = "No valid input file was given, please check the given filename.";
    CV_Error(CV_StsBadArg, error_message);
  }
  std::string line;
  std::string name, labelStr;
  // read lines from file one by one
  while (getline(file, line)) {
    std::stringstream liness(line);
    // read first word which is person name
    getline(liness, name, separator);
    // read second word which is integer label
    getline(liness, labelStr);
    if(!name.empty() && !labelStr.empty()) {
      names.push_back(name);
      // convert label from string format to integer
      int label = atoi(labelStr.c_str());
      labels.push_back(label);
      // add (integer label, person name) pair to map
      labelNameMap[label] = name;
    }
  }
}

static void ReadDescriptors(const std::string& filename, std::vector<int>& faceLabels, std::vector<dlib::matrix<float,0,1>>& faceDescriptors, char separator = ';')
{
  std::ifstream file(filename.c_str(), std::ifstream::in);
  if (!file) {
    std::string error_message = "No valid input file was given, please check the given filename.";
    CV_Error(CV_StsBadArg, error_message);
  }
  // each line has:
  // 1st element = face label
  // rest 128 elements = descriptor elements
  std::string line;
  std::string faceLabel;
  // valueStr = one element of descriptor in string format
  // value = one element of descriptor in float
  std::string valueStr;
  float value;
  std::vector<float> faceDescriptorVec;
  // read lines from file one by one
  while (getline(file, line)) {
    std::stringstream liness(line);
    // read face label
    // read first word on a line till separator
    getline(liness, faceLabel, separator);
    if(!faceLabel.empty()) {
      faceLabels.push_back(std::atoi(faceLabel.c_str()));
    }

    faceDescriptorVec.clear();
    // read rest of the words one by one using separator
    while (getline(liness, valueStr, separator)) {
      if (!valueStr.empty()) {
        // convert descriptor element from string to float
        faceDescriptorVec.push_back(atof(valueStr.c_str()));
      }
    }
    // convert face descriptor from vector of float to Dlib's matrix format
    dlib::matrix<float, 0, 1> faceDescriptor = dlib::mat(faceDescriptorVec);
    faceDescriptors.push_back(faceDescriptor);
  }
}

// find nearest face descriptor from vector of enrolled faceDescriptor
// to a query face descriptor
void NearestNeighbor(dlib::matrix<float, 0, 1>& faceDescriptorQuery,
                    std::vector<dlib::matrix<float, 0, 1>>& faceDescriptors,
                    std::vector<int>& faceLabels, int& label, float& minDistance)
{
  int minDistIndex = 0;
  minDistance = 1.0;
  label = -1;
  // Calculate Euclidean distances between face descriptor calculated on face dectected
  // in current frame with all the face descriptors we calculated while enrolling faces
  // Calculate minimum distance and index of this face
  for (int i = 0; i < faceDescriptors.size(); i++) {
    double distance = length(faceDescriptors[i] - faceDescriptorQuery);
    if (distance < minDistance) {
      minDistance = distance;
      minDistIndex = i;
    }
  }
  // Dlib specifies that in general, if two face descriptor vectors have a Euclidean
  // distance between them less than 0.6 then they are from the same
  // person, otherwise they are from different people.

  // This threshold will vary depending upon number of images enrolled
  // and various variations (illuminaton, camera quality) between
  // enrolled images and query image
  // We are using a threshold of 0.5
  // if minimum distance is greater than a threshold
  // assign integer label -1 i.e. unknown face
  if (minDistance > THRESHOLD){
    label = -1;
  } else {
    label = faceLabels[minDistIndex];
  }
}

static std::string GetEpcohTime()
{
  using namespace  std::chrono;
  milliseconds ms = duration_cast< milliseconds >
    (system_clock::now().time_since_epoch());
  return std::to_string(ms.count());
}

int main(int argc, char** argv)
{
  //auto jsonFile("../data/bkup_DataPaths.json");
  auto jsonFile("../data/DataPaths.json");

  JsonParser parser(jsonFile);
  // Watchout for the JsonParser lifetime. as parser object
  // is moved and not copied. This is the behaviour of the
  // RapidJson.

  auto labelNameFile(parser.Value("LableFile"));
  auto predictorPath(parser.Value("PredictorFile"));
  auto faceRecognitionModelPath(parser.Value("FaceRecModelFile"));
  auto faceDescriptorFile(parser.Value("DescriptorFile"));
  auto videoFile(parser.Value("TestVideoFile"));
  auto imgCapturePath(parser.Value("ImgCapturePath"));

  dlib::frontal_face_detector faceDetector = dlib::get_frontal_face_detector();
  dlib::shape_predictor landmarkDetector;
  anet_type net;

  dlib::deserialize(predictorPath) >> landmarkDetector;
  dlib::deserialize(faceRecognitionModelPath) >> net;


  // read names, labels and labels-name-mapping from file
  std::map<int, std::string> labelNameMap;
  std::vector<std::string> names;
  std::vector<int> labels;
  ReadLableNameMap(labelNameFile, names, labels, labelNameMap);

  // read descriptors of enrolled faces from file
  std::vector<int> faceLabels;
  std::vector<dlib::matrix<float,0,1>> faceDescriptors;
  ReadDescriptors(faceDescriptorFile, faceLabels, faceDescriptors);

  // Create a VideoCapture object
  //cv::VideoCapture cap(0);
  //cv::VideoCapture cap("../data/tom_interview.mp4");
  cv::VideoCapture cap(videoFile);

  // Check if OpenCV is able to read feed from camera
  if (!cap.isOpened()) {
    std::cerr << "Unable to find the file " << videoFile.c_str() <<"\n";
    return 1;
  }
  int count = 0;
  while (true) {
    // Capture frame
    cv::Mat im;
    cap >> im;

    // If the frame is empty, break immediately
    if (im.empty()){
      break;
    }

    // We will be processing frames after an interval
    // of SKIP_FRAMES to increase processing speed
    if ((count % SKIP_FRAMES) == 0) {

      // convert image from BGR to RGB
      // because Dlib used RGB format
      cv::Mat imRGB = im.clone();
      cv::cvtColor(im, imRGB, cv::COLOR_BGR2RGB);
      // convert OpenCV image to Dlib's cv_image object, then to Dlib's matrix object
      // Dlib's dnn module doesn't accept Dlib's cv_image template
      dlib::matrix<dlib::rgb_pixel> imDlib(dlib::mat(dlib::cv_image<dlib::rgb_pixel>(imRGB)));

      // detect faces in image
      std::vector<dlib::rectangle> faceRects = faceDetector(imDlib);
      // Now process each face we found
      for (int i = 0; i < faceRects.size(); i++) {
        auto localTime(GetEpcohTime());
        std::string imgStorePath(imgCapturePath);
        std::string imgName(localTime);
        imgStorePath += imgName + ".jpg";
        cv::imwrite(imgStorePath, im);

        // Find facial landmarks for each detected face
        dlib::full_object_detection landmarks = landmarkDetector(imDlib, faceRects[i]);

        // object to hold preProcessed face rectangle cropped from image
        dlib::matrix<rgb_pixel> face_chip;

        // original face rectangle is warped to 150x150 patch.
        // Same pre-processing was also performed during training.
        dlib::extract_image_chip(imDlib, get_face_chip_details(landmarks,150,0.25), face_chip);

        // Compute face descriptor using neural network defined in Dlib.
        // It is a 128D vector that describes the face in img identified by shape.
        dlib::matrix<float,0,1> faceDescriptorQuery = net(face_chip);

        // Find closest face enrolled to face found in frame
        int label;
        float minDistance;
        NearestNeighbor(faceDescriptorQuery, faceDescriptors, faceLabels, label, minDistance);
        // Name of recognized person from map
        std::string name = labelNameMap[label];

        // Draw a rectangle for detected face
        cv::Point2d p1 = cv::Point2d(faceRects[i].left(), faceRects[i].top());
        cv::Point2d p2 = cv::Point2d(faceRects[i].right(), faceRects[i].bottom());
        cv::rectangle(im, p1, p2, cv::Scalar(0, 0, 255), 1, cv::LINE_8);

        // Draw circle for face recognition
        cv::Point2d center = cv::Point((faceRects[i].left() + faceRects[i].right())/2.0,
        (faceRects[i].top() + faceRects[i].bottom())/2.0 );
        int radius = static_cast<int> ((faceRects[i].bottom() - faceRects[i].top())/2.0);
        cv::circle(im, center, radius, cv::Scalar(0, 255, 0), 1, cv::LINE_8);

        // Write text on image specifying identified person and minimum distance
        std::stringstream stream;
        stream << name << " ";
        stream << std::fixed << std::setprecision(4) << minDistance;
        std::string text(stream.str());
        cv::putText(im, text, p1, cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 0, 0), 2);
      }

      // Show result
      cv::imshow("video plyaback", im);
      int k = cv::waitKey(30);
      // Quit when Esc is pressed
      if (k == 27) {
        break;
      }
    }
  // Counter used for skipping frames
  count += 1;
  }
  cv::destroyAllWindows();

  return 0;
}
