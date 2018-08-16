#include "DrawingUtils.hpp"
#include <opencv2/imgproc.hpp>

/*
DrawingUtils::DrawingUtils(cv::Mat &img):
  Image(img.clone())
{
  // Empty.
}
*/

DrawingUtils::DrawingUtils()
{
  // Empty.
}

DrawingUtils::~DrawingUtils()
{
  // Empty.
}

void DrawingUtils::BoundinBox(cv::Mat &im, std::vector<dlib::rectangle> &bb, const std::string &text)
{
  for(auto &v: bb) {
    cv::Point2d p1 = cv::Point2d(v.left(), v.top());
    cv::Point2d p2 = cv::Point2d(v.right(), v.bottom());
    cv::rectangle(im, p1, p2, cv::Scalar(0, 0, 255), 1, cv::LINE_8);
    cv::putText(im, text.c_str(), p1, cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 0, 0), 2);
  }
  return;
}

void DrawingUtils::Circle(cv::Mat &im, std::vector<dlib::rectangle> &bb)
{
  for(auto &v:bb) {
    cv::Point2d center = cv::Point((v.left() + v.right())/2.0,
        (v.top() + v.bottom())/2.0 );
    int radius = static_cast<int> ((v.bottom() - v.top())/2.0);
    cv::circle(im, center, radius, cv::Scalar(0, 255, 0), 1, cv::LINE_8);
  }
  return;
}
