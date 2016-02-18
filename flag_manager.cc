#include "flag_manager.hh"

DEFINE_string(type, "", "filter type ... grayscale, meanshift, red, green ,blue");
DEFINE_string(file, "", "filename");

tj::FilterManager::FilterManager(int argc, char *argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
}

std::string tj::FilterManager::getFilterTypeName() {
  if (FLAGS_type.empty()) {
    return "Not Found";
  }
  return FLAGS_type;
}

int tj::FilterManager::getFilterType() {
  if (FLAGS_type.empty()) {
    return -1;
  }
  if (FLAGS_type == "grayscale") {
    return 1;
  } else if (FLAGS_type == "meanshift") {
    return 2;
  } else if (FLAGS_type == "green") {
    return 3;
  } else if (FLAGS_type == "blue") {
    return 4;
  } else if (FLAGS_type == "red") {
    return 5;
  }
  return -1;
}

std::string tj::FilterManager::getFilePath() {
  if (FLAGS_file.empty()) {
    return NULL;
  }
  return FLAGS_file;
}
