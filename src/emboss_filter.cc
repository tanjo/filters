#include "emboss_filter.hh"

cv::Mat tj::EmbossFilter::apply(const cv::Mat &src) {
  cv::Mat kernel = (cv::Mat_<float>(3, 3) <<
    -1, -1, 0,
    -1,  1, 1,
     0,  1, 1);
  cv::Mat dst;
  cv::filter2D(src, dst, -1, kernel);
  return dst;
}
