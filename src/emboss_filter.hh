#ifndef __EMBOSS_FILTER_HH__
#define __EMBOSS_FILTER_HH__

#include <opencv2/opencv.hpp>
#include "base_filter.hh"

namespace tj {
  class EmbossFilter: public BaseFilter {
  public:
    cv::Mat apply(const cv::Mat &src);
  };
}

#endif // __EMBOSS_FILTER_HH__
