#include "affine_filter.hh"

cv::Mat tj::AffineFilter::apply(const cv::Mat &src) {
  cv::Mat dst;
  // 時計周りに 90°
  cv::transpose(src, dst);
  cv::flip(dst, dst, 1);
  return dst;
}
