#ifndef __GREEN_FILTER_HH__
#define __GREEN_FILTER_HH__

#include <opencv2/opencv.hpp>
#include "base_filter.hh"

namespace tj {
  class GreenFilter: public BaseFilter {
  public:
    cv::Mat apply(const cv::Mat &src);
  };
}

#endif // __GREEN_FILTER_HH__
