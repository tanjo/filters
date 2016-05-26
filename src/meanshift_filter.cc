#include "meanshift_filter.hh"

cv::Mat tj::MeanShiftFilter::apply(const cv::Mat &src) {
  float sp = 30.0; // 空間窓の半径
  float sr = 30.0; // 色空間窓の半径
  int max_level = 2;
  CvTermCriteria termcrit = CvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 5, 1);
  cv::Mat dst;
  cv::pyrMeanShiftFiltering(src, dst, sp, sr, max_level, termcrit);
  return dst;
}
