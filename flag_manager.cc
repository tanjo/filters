#include "flag_manager.hh"

DEFINE_string(type, "", "filter type ... grayscale, meanshift, red, green ,blue, revival, negative, emboss, sharp, gaussianblur, dot, simple");
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
    return GrayScale;
  } else if (FLAGS_type == "meanshift") {
    return MeanShift;
  } else if (FLAGS_type == "green") {
    return Green;
  } else if (FLAGS_type == "blue") {
    return Blue;
  } else if (FLAGS_type == "red") {
    return Red;
  } else if (FLAGS_type == "negative") {
    return Negative;
  } else if (FLAGS_type == "emboss") {
    return Emboss;
  } else if (FLAGS_type == "sharp") {
    return Sharp;
  } else if (FLAGS_type == "gaussianblur") {
    return GaussianBlur;
  } else if (FLAGS_type == "dot") {
    return Dot;
  } else if (FLAGS_type == "simple") {
    return Simple;
  }
  return -1;
}

std::string tj::FilterManager::getFilePath() {
  if (FLAGS_file.empty()) {
    return std::string();
  }
  return FLAGS_file;
}
