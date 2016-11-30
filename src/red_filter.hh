#ifndef __RED_FILTER_HH__
#define __RED_FILTER_HH__

#include <opencv2/opencv.hpp>
#include "base_filter.hh"

namespace tj {
  class RedFilter: public BaseFilter {
  public:
    cv::Mat apply(const cv::Mat &src);
  };
}

#endif // __RED_FILTER_HH__
