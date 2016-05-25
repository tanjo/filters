#ifndef __GAUSSIANBLUR_FILTER_HH__
#define __GAUSSIANBLUR_FILTER_HH__

#include <opencv2/opencv.hpp>
#include "base_filter.hh"

namespace tj {
  class GaussianBlurFilter: public BaseFilter {
  public:
    cv::Mat apply(const cv::Mat &src);
  };
}

#endif // __GAUSSIANBLUR_FILTER_HH__
