#ifndef __MEANSHIFT_FILTER_HH__
#define __MEANSHIFT_FILTER_HH__

#include <opencv2/opencv.hpp>
#include "base_filter.hh"

namespace tj {
  class MeanShiftFilter: public BaseFilter {
  public:
    cv::Mat apply(const cv::Mat &src);
  };
}

#endif // __MEANSHIFT_FILTER_HH__
