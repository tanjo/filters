#ifndef __NEGATIVE_FILTER_HH__
#define __NEGATIVE_FILTER_HH__

#include <opencv2/opencv.hpp>
#include "base_filter.hh"

namespace tj {
  class NegativeFilter: public BaseFilter {
  public:
    cv::Mat apply(const cv::Mat &src);
  };
}

#endif // __NEGATIVE_FILTER_HH__
