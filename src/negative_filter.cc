#include "negative_filter.hh"

cv::Mat tj::NegativeFilter::apply(const cv::Mat &src) {
  return ~src;
}
