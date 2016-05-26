#include "grayscale_filter.hh"

cv::Mat tj::GrayScaleFilter::apply(const cv::Mat &src) {
  cv::Mat dst;
  cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
  return dst;
}
