#include "sharp_filter.hh"

cv::Mat tj::SharpFilter::apply(const cv::Mat &src) {
  cv::Mat kernel = (cv::Mat_<float>(3, 3) <<
     0, -1,  0,
    -1,  5, -1,
     0, -1,  0);
  cv::Mat dst;
  cv::filter2D(src, dst, -1, kernel);
  return dst;
}
