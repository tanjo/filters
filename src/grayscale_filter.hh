#ifndef __GRAYSCALE_FILTER_HH__
#define __GRAYSCALE_FILTER_HH__

#include <opencv2/opencv.hpp>
#include "base_filter.hh"

namespace tj {
  class GrayScaleFilter: public BaseFilter {
  public:
    cv::Mat apply(const cv::Mat &src);
  };
}

#endif // __GRAYSCALE_FILTER_HH__
