#include "image_scaler.hpp"
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <fstream>

namespace fs = std::filesystem;

void ImageScaler::scale_img(fs::path img_path, fs::path output_path, double width) {
  cv::Mat img_in = cv::imread(img_path);
  cv::Mat img_out;
  double img_w = img_in.cols;
  double scaling_factor = width / img_w;
  cv::resize(img_in, img_out, cv::Size(), scaling_factor, scaling_factor, cv::INTER_AREA);
  std::ofstream file(output_path / img_path.filename());
  cv::imwrite(output_path / img_path.filename(), img_out);
  file.close();
}

void ImageScaler::scale_imgs(fs::path folder_path, fs::path output_path, double width) {
  for (auto const& img : fs::directory_iterator{folder_path}) {
    scale_img(img.path(), output_path, width);
  }
}
