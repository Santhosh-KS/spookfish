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

void DrawingUtils::BoundinBox(const cv::Mat &im,
    const std::vector<dlib::rectangle> &bb,
    const std::vector<std::string> &textVec)
{
  std::cout << "bb = " << bb.size() << " txt = " << textVec.size() << "\n";
  for(auto i = 0; i < bb.size(); i++) {
    cv::Point2d p1 = cv::Point2d(bb[i].left(), bb[i].top());
    cv::Point2d p2 = cv::Point2d(bb[i].right(), bb[i].bottom());
    cv::rectangle(im, p1, p2, cv::Scalar(0, 0, 255), 1, cv::LINE_8);
    cv::putText(im, textVec[i].c_str(), p1, cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 0, 0), 2);
  }
  return;
}

void DrawingUtils::Circle(const cv::Mat &im, const std::vector<dlib::rectangle> &bb)
{
  for(auto &v:bb) {
    cv::Point2d center = cv::Point((v.left() + v.right())/2.0,
        (v.top() + v.bottom())/2.0 );
    int radius = static_cast<int> ((v.bottom() - v.top())/2.0);
    cv::circle(im, center, radius, cv::Scalar(0, 255, 0), 1, cv::LINE_8);
  }
  return;
}
