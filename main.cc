#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "flag_manager.hh"
#include "grayscale_filter.hh"
#include "green_filter.hh"
#include "blue_filter.hh"
#include "red_filter.hh"
#include "meanshift_filter.hh"
#include "negative_filter.hh"
#include "emboss_filter.hh"
#include "gaussianblur_filter.hh"
#include "sharp_filter.hh"

int main(int argc, char *argv[]) {

  std::shared_ptr<tj::FilterManager> manager(new tj::FilterManager(argc, argv));

  if (manager->getFilterType() == -1) {
    std::cout << "Error: ./filters --type XXX --file XXXXXX.jpg" << std::endl;
    std::cout << "Filter List: GrayScale, MeanShift, Green, Blue, Red, Revival, Negative, Emboss, Sharp, GaussianBlur, Dot, Simple" << std::endl;
    return -1;
  }

  if (manager->getFilePath().empty()||manager->getFilePath().length() == 0) {
    std::cout << "Error: ./filters --type XXX --file XXXXXX.jpg" << std::endl;
    return -1;
  }

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
  std::shared_ptr<tj::BaseFilter> p;

  std::cout << manager->getFilterTypeName() << " processing ..." << std::endl;
  switch (manager->getFilterType()) {
    case tj::GrayScale: {
      p.reset(new tj::GrayScaleFilter());
      dst = p->apply(src);
      break;
    }
    case tj::MeanShift: {
      p.reset(new tj::MeanShiftFilter());
      dst = p->apply(src);
      break;
    }
    case tj::Green: {
      p.reset(new tj::GreenFilter());
      dst = p->apply(src);
      break;
    }
    case tj::Blue: {
      p.reset(new tj::BlueFilter());
      dst = p->apply(src);
      break;
    }
    case tj::Red: {
      p.reset(new tj::RedFilter());
      dst = p->apply(src);
      break;
    }
    case tj::Negative: {
      p.reset(new tj::NegativeFilter());
      dst = p->apply(src);
      break;
    }
    case tj::Emboss: {
      p.reset(new tj::EmbossFilter());
      dst = p->apply(src);
      break;
    }
    case tj::Sharp: {
      p.reset(new tj::SharpFilter());
      dst = p->apply(src);
      break;
    }
    case tj::GaussianBlur: {
      p.reset(new tj::GaussianBlurFilter());
      dst = p->apply(src);
      break;
    }
    case tj::Dot: {
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
