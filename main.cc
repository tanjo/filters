#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "flag_manager.hh"

int main(int argc, char *argv[]) {

  std::shared_ptr<tj::FilterManager> manager(new tj::FilterManager(argc, argv));

  cv::Mat src = cv::imread(manager->getFilePath());

  cv::Mat dst = src.clone();

  if (manager->getFilterType() == 1) {
    std::cout << "grayscale processing ..." << std::endl;
    cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
  } else if (manager->getFilterType() == 2) {
    std::cout << "meanshift processing ..." << std::endl;
    float sp = 30.0; // 空間窓の半径
    float sr = 30.0; // 色空間窓の半径
    int max_level = 2;
    CvTermCriteria termcrit = CvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 5, 1);
    cv::pyrMeanShiftFiltering(src, dst, sp, sr, max_level, termcrit);
  } else if (manager->getFilterType() == 3) {
    std::cout << "only green processing ..." << std::endl;

    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(gray, gray, cv::COLOR_GRAY2BGR);

    cv::Mat hsv;
    cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);

    std::vector<cv::Mat> mats;
    cv::split(hsv, mats);

    cv::Mat h1, h2;
    cv::threshold(mats[0], h1, 35, 255, cv::THRESH_BINARY);
    cv::threshold(mats[0], h2, 80, 255, cv::THRESH_BINARY_INV);
    cv::Mat mask = h1 & h2;

    cv::cvtColor(mask, mask, cv::COLOR_GRAY2BGR);

    cv::bitwise_and(src, mask, dst);

    mask = ~mask;

    cv::Mat gray2;
    cv::bitwise_and(gray, mask, gray2);

    dst = dst + gray2;

  } else if (manager->getFilterType() == 4) {
    std::cout << "only blue processing ..." << std::endl;

    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(gray, gray, cv::COLOR_GRAY2BGR);

    cv::Mat hsv;
    cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);

    std::vector<cv::Mat> mats;
    cv::split(hsv, mats);

    cv::Mat h1, h2;
    cv::threshold(mats[0], h1, 80, 255, cv::THRESH_BINARY);
    cv::threshold(mats[0], h2, 135, 255, cv::THRESH_BINARY_INV);
    cv::Mat mask = h1 & h2;

    cv::cvtColor(mask, mask, cv::COLOR_GRAY2BGR);

    cv::bitwise_and(src, mask, dst);

    mask = ~mask;

    cv::Mat gray2;
    cv::bitwise_and(gray, mask, gray2);

    dst = dst + gray2;
  } else if (manager->getFilterType() == 5) {
    std::cout << "only red processing ..." << std::endl;

    cv::Mat gray;
    cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
    cv::cvtColor(gray, gray, cv::COLOR_GRAY2BGR);

    cv::Mat hsv;
    cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);

    std::vector<cv::Mat> mats;
    cv::split(hsv, mats);

    cv::Mat h1, h2;
    cv::threshold(mats[0], h1, 135, 255, cv::THRESH_BINARY);
    cv::threshold(mats[0], h2, 35, 255, cv::THRESH_BINARY_INV);
    cv::Mat mask = h1 | h2;

    cv::cvtColor(mask, mask, cv::COLOR_GRAY2BGR);

    cv::bitwise_and(src, mask, dst);

    mask = ~mask;

    cv::Mat gray2;
    cv::bitwise_and(gray, mask, gray2);

    dst = dst + gray2;
  } else {
    std::cout << "can't be processed" << std::endl;
    return -1;
  }

  std::string filename = manager->getFilePath();
  filename += "-" + manager->getFilterTypeName() + ".png";
  cv::imwrite(filename, dst);
  std::cout << "finish: " << filename << std::endl;
}
