#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "flag_manager.hh"

int main(int argc, char *argv[]) {

  std::shared_ptr<tj::FilterManager> manager(new tj::FilterManager(argc, argv));

  cv::Mat src = cv::imread(manager->getFilePath(), cv::IMREAD_UNCHANGED);
  std::vector<cv::Mat> src_mv;
  cv::split(src, src_mv);
  cv::Mat alpha;
  int channel = src_mv.size();
  if (channel == 4) {
    alpha = src_mv[3].clone();
  }
  src = cv::imread(manager->getFilePath());
  cv::Mat dst = src.clone();

  switch (manager->getFilterType()) {
    case tj::GrayScale: {
      std::cout << "grayscale processing ..." << std::endl;
      cv::cvtColor(src, dst, cv::COLOR_BGR2GRAY);
      break;
    }
    case tj::MeanShift: {
        std::cout << "meanshift processing ..." << std::endl;
        float sp = 30.0; // 空間窓の半径
        float sr = 30.0; // 色空間窓の半径
        int max_level = 2;
        CvTermCriteria termcrit = CvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 5, 1);
        cv::pyrMeanShiftFiltering(src, dst, sp, sr, max_level, termcrit);
        break;
    }
    case tj::Green: {
      std::cout << "only green processing ..." << std::endl;
      cv::Mat gray;
      cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);
      cv::cvtColor(gray, gray, cv::COLOR_GRAY2BGR);
      cv::Mat hsv;
      cv::cvtColor(src, hsv, cv::COLOR_BGR2HSV);
      std::vector<cv::Mat> mats;
      cv::split(hsv, mats);
      cv::Mat h1, h2;
      cv::threshold(mats[0], h1, 20, 255, cv::THRESH_BINARY);
      cv::threshold(mats[0], h2, 80, 255, cv::THRESH_BINARY_INV);
      cv::Mat mask = h1 & h2;
      cv::cvtColor(mask, mask, cv::COLOR_GRAY2BGR);
      cv::bitwise_and(src, mask, dst);
      mask = ~mask;
      cv::Mat gray2;
      cv::bitwise_and(gray, mask, gray2);
      dst = dst + gray2;
      break;
    }
    case tj::Blue: {
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
      break;
    }
    case tj::Red: {
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
      cv::threshold(mats[0], h2, 20, 255, cv::THRESH_BINARY_INV);
      cv::Mat mask = h1 | h2;
      cv::cvtColor(mask, mask, cv::COLOR_GRAY2BGR);
      cv::bitwise_and(src, mask, dst);
      mask = ~mask;
      cv::Mat gray2;
      cv::bitwise_and(gray, mask, gray2);
      dst = dst + gray2;
      break;
    }
    case tj::Revival: {
      // 参考：色特徴のコード化を用いた画像の色復元
      std::cout << "Sorry, comming soon." << std::endl;
      return -1;
    }
    case tj::Negative: {
      std::cout << "negative processing ..." << std::endl;
      dst = ~dst;
      break;
    }
    case tj::Emboss: {
      std::cout << "emboss processing ..." << std::endl;
      cv::Mat kernel = (cv::Mat_<float>(3, 3) <<
        -1, -1, 0,
        -1,  1, 1,
         0,  1, 1);
      cv::filter2D(src, dst, -1, kernel);
      break;
    }
    case tj::Sharp: {
      std::cout << "median processing ..." << std::endl;
      cv::Mat kernel = (cv::Mat_<float>(3, 3) <<
         0, -1,  0,
        -1,  5, -1,
         0, -1,  0);
      cv::filter2D(src, dst, -1, kernel);
      break;
    }
    case tj::GaussianBlur: {
      std::cout << "median processing ..." << std::endl;
      cv::blur(src, dst, cv::Size(5, 5));
      break;
    }
    case tj::Dot: {
      std::cout << "dot processing ..." << std::endl;
      cv::Mat reshaped = src.reshape(1, src.cols * src.rows);
      cv::Mat reshaped32f;
      reshaped.convertTo(reshaped32f, CV_32FC1, 1.0 / 255.0);
      cv::Mat labels;
      int cluster_number = 10;
      cv::TermCriteria criteria { cv::TermCriteria::COUNT, 100, 1};
      cv::Mat centers;
      cv::kmeans(reshaped32f, cluster_number, labels, criteria, 1, cv::KMEANS_RANDOM_CENTERS, centers);

      cv::MatIterator_<cv::Vec3b> begin = dst.begin<cv::Vec3b>();
      cv::MatIterator_<cv::Vec3b> end = dst.end<cv::Vec3b>();
      cv::MatConstIterator_<int> lbegin = labels.begin<int>();

      cv::Mat centers_u8;
      centers.convertTo(centers_u8, CV_8UC1, 255.0);
      cv::Mat centers_u8c3 = centers_u8.reshape(3);

      while (begin != end) {
        const cv::Vec3b& rgb = centers_u8c3.ptr<cv::Vec3b>(*lbegin)[0];
        *begin = rgb;
        ++begin;
        ++lbegin;
      }

      break;
    }
    case tj::Simple: {
      std::cout << "simple processing ..." << std::endl;
      cv::Mat reshaped = src.reshape(1, src.cols * src.rows);
      cv::Mat reshaped32f;
      reshaped.convertTo(reshaped32f, CV_32FC1, 1.0 / 255.0);
      cv::Mat labels;
      int cluster_number = 2;
      cv::TermCriteria criteria { cv::TermCriteria::COUNT, 100, 1};
      cv::Mat centers;
      cv::kmeans(reshaped32f, cluster_number, labels, criteria, 1, cv::KMEANS_RANDOM_CENTERS, centers);

      cv::MatIterator_<cv::Vec3b> begin = dst.begin<cv::Vec3b>();
      cv::MatIterator_<cv::Vec3b> end = dst.end<cv::Vec3b>();
      cv::MatConstIterator_<int> lbegin = labels.begin<int>();

      cv::Mat centers_u8;
      centers.convertTo(centers_u8, CV_8UC1, 255.0);
      cv::Mat centers_u8c3 = centers_u8.reshape(3);

      while (begin != end) {
        const cv::Vec3b& rgb = centers_u8c3.ptr<cv::Vec3b>(*lbegin)[0];
        *begin = rgb;
        ++begin;
        ++lbegin;
      }
      break;
    }
    default: {
      std::cout << "can't be processed" << std::endl;
      return -1;
    }
  }

  printf("%d\n", dst.channels());

  if (dst.channels() == 1) {
    cv::cvtColor(dst, dst, cv::COLOR_GRAY2BGR);
  }

  if (channel == 4) {
    std::vector<cv::Mat> dst_mv;
    cv::split(dst, dst_mv);
    dst_mv.push_back(alpha);
    cv::merge(dst_mv, dst);
  }

  std::string filename = manager->getFilePath();
  std::vector<int> compression_params;
  compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
  compression_params.push_back(9);

  filename += "-" + manager->getFilterTypeName() + ".png";
  cv::imwrite(filename, dst, compression_params);
  std::cout << "finish: " << filename << std::endl;
}
