#ifndef __BASE_FILTER_HH__
#define __BASE_FILTER_HH__

#include <opencv2/opencv.hpp>

namespace tj {
  class BaseFilter {
  public:
    virtual cv::Mat apply(const cv::Mat &src);
  };
}

#endif // __BASE_FILTER_HH__
