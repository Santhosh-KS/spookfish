#ifndef DRAWING_UTILS_HPP
#define DRAWING_UTILS_HPP
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

#include "NotCopyable.hpp"
#include <opencv2/highgui.hpp>
#include <dlib/image_io.h>
#include <dlib/opencv.h>

class DrawingUtils : public NotCopyable
{
  private:
    cv::Mat Image;
  public:
    //explicit DrawingUtils(cv::Mat img);
    DrawingUtils();
    ~DrawingUtils();
    void BoundinBox(const cv::Mat &im,
      const std::vector<dlib::rectangle> &bb, const std::vector<std::string> &);
    void Circle(const cv::Mat &im, const std::vector<dlib::rectangle> &bb);
};

#endif // DRAWING_UTILS_HPP
