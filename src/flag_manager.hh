#ifndef __FLAG_MANAGER_HH__
#define __FLAG_MANAGER_HH__

#include <gflags/gflags.h>
#include <iostream>
#include <fstream>
#include <string>

namespace tj {

  enum FilterType {
    GrayScale = 0,
    MeanShift,
    Green,
    Blue,
    Red,
    Negative,
    Emboss,
    Sharp,
    GaussianBlur,
    Dot,
    Simple,
    Affine
  };

  class FilterManager {
  public:
      FilterManager(int argc, char *argv[]);

      int getFilterType();
      std::string getFilterTypeName();
      std::string getFilePath();
  };

}

#endif // __FLAG_MANAGER_HH__
