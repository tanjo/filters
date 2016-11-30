#ifndef __SIMPLE_FILTER_HH__
#define __SIMPLE_FILTER_HH__

#include <opencv2/opencv.hpp>
#include "base_filter.hh"

namespace tj {
  class SimpleFilter: public BaseFilter {
  public:
    cv::Mat apply(const cv::Mat &src);
  };
}

#endif // __SIMPLE_FILTER_HH__
