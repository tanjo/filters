#include "blue_filter.hh"

cv::Mat tj::BlueFilter::apply(const cv::Mat &src) {
  cv::Mat gray;
  cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
  cv::cvtColor(gray, gray, cv::COLOR_GRAY2BGR);
  cv::Mat hsv;
  cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
  std::vector<cv::Mat> mats;
  cv::split(hsv, mats);
  cv::Mat h1, h2;
  cv::threshold(mats[0], h1, 80, 255, cv::THRESH_BINARY);
  cv::threshold(mats[0], h2, 135, 255, cv::THRESH_BINARY_INV);
  cv::Mat mask = h1 & h2;
  cv::cvtColor(mask, mask, cv::COLOR_GRAY2BGR);
  cv::Mat dst;
  cv::bitwise_and(src, mask, dst);
  mask = ~mask;
  cv::Mat gray2;
  cv::bitwise_and(gray, mask, gray2);
  dst = dst + gray2;
  return dst;
}
