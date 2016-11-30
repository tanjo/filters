#ifndef __BLUE_FILTER_HH__
#define __BLUE_FILTER_HH__

#include <opencv2/opencv.hpp>
#include "base_filter.hh"

namespace tj {
  class BlueFilter: public BaseFilter {
  public:
    cv::Mat apply(const cv::Mat &src);
  };
}

#endif // __BLUE_FILTER_HH__
