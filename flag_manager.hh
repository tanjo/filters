#ifndef __FLAG_MANAGER_HH__
#define __FLAG_MANAGER_HH__

#include <gflags/gflags.h>
#include <iostream>
#include <fstream>
#include <string>

namespace tj {

  enum FilterType {
    GrayScale = 1,
    MeanShift = 2,
    Green = 3,
    Blue = 4,
    Red = 5,
    Revival = 6,
    Negative = 7,
    Emboss = 8,
    Sharp = 9,
    GaussianBlur = 10,
    Dot = 11,
    Simple = 12
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
