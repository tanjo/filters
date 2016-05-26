#include "gaussianblur_filter.hh"

cv::Mat tj::GaussianBlurFilter::apply(const cv::Mat &src) {
  cv::Mat dst;
  cv::blur(src, dst, cv::Size(5, 5));
  return dst;
}
