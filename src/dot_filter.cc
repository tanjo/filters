#include "dot_filter.hh"

cv::Mat tj::DotFilter::apply(const cv::Mat &src) {
  cv::Mat dst = src.clone();
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
  return dst;
}
