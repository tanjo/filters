#ifndef __AFFINE_FILTER_HH__
#define __AFFINE_FILTER_HH__

#include <cmath>
#include <opencv2/opencv.hpp>
#include "base_filter.hh"

namespace tj {
  class AffineFilter: public BaseFilter {
  public:
    cv::Mat apply(const cv::Mat &src);
  };
}

#endif // __AFFINE_FILTER_HH__
