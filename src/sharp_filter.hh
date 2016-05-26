#ifndef __SHARP_FILTER_HH__
#define __SHARP_FILTER_HH__

#include <opencv2/opencv.hpp>
#include "base_filter.hh"

namespace tj {
  class SharpFilter: public BaseFilter {
  public:
    cv::Mat apply(const cv::Mat &src);
  };
}

#endif // __SHARP_FILTER_HH__
