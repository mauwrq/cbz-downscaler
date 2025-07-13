#include "image_converter.hpp"
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <fstream>

namespace fs = std::filesystem;

void ImageConverter::to_jpg(fs::path img_path, fs::path output_path) {
  std::string ext = img_path.extension().string();
  std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
  if (ext != ".jpg") {
    fs::path jpg_path = output_path / img_path.filename().replace_extension(".jpg");
    std::ofstream file(jpg_path);
    cv::Mat non_jpg = cv::imread(img_path);
    cv::imwrite(jpg_path, non_jpg, std::vector<int>{cv::IMWRITE_JPEG_QUALITY, 95});
    file.close();
  }
  else {
    fs::copy_file(img_path, output_path / img_path.filename());
  }
}

void ImageConverter::to_jpgs(fs::path folder_path, fs::path output_path) {
  for (auto const& img : fs::directory_iterator{folder_path}) {
    to_jpg(img.path(), output_path);
  }
}

void ImageConverter::to_webp(fs::path img_path, fs::path output_path) {
  std::string ext = img_path.extension().string();
  std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
  if (ext != ".webp") {
    fs::path webp_path = output_path / img_path.filename().replace_extension(".webp");
    std::ofstream file(webp_path);
    cv::Mat non_jpg = cv::imread(img_path);
    cv::imwrite(webp_path, non_jpg, std::vector<int>{cv::IMWRITE_WEBP_QUALITY, 95});
    file.close();
  }
  else {
    fs::copy_file(img_path, output_path / img_path.filename());
  }
}

void ImageConverter::to_webps(fs::path folder_path, fs::path output_path) {
  for (auto const& img : fs::directory_iterator{folder_path}) {
    to_webp(img.path(), output_path);
  }
}
