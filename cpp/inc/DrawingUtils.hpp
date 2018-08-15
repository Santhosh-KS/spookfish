#ifndef DRAWING_UTILS_HPP
#define DRAWING_UTILS_HPP

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
    void BoundinBox(cv::Mat &im, std::vector<dlib::rectangle> &bb);
    void Circle(cv::Mat &im, std::vector<dlib::rectangle> &bb);
};

#endif // DRAWING_UTILS_HPP
