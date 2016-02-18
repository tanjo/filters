#ifndef __FLAG_MANAGER_HH__
#define __FLAG_MANAGER_HH__

#include <gflags/gflags.h>
#include <iostream>
#include <fstream>
#include <string>

namespace tj {

  class FilterManager {
  public:
      FilterManager(int argc, char *argv[]);

      int getFilterType();
      std::string getFilterTypeName();
      std::string getFilePath();
  };

}

#endif // __FLAG_MANAGER_HH__
