#include <iostream>
#include <string.h>
#include <zip.h>
#include <fstream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include "cbz_unzipper.hpp"
#include "image_scaler.hpp"
#include "image_converter.hpp"

namespace fs = std::filesystem;

void scale_img(fs::path img_path, fs::path output_path, double width) {
  cv::Mat img_in = cv::imread(img_path);
  cv::Mat img_out;
  double img_w = img_in.cols;
  double scaling_factor = width / img_w;
  cv::resize(img_in, img_out, cv::Size(), scaling_factor, scaling_factor, cv::INTER_AREA);
  std::ofstream file(output_path / img_path.filename());
  cv::imwrite(output_path / img_path.filename(), img_out);
  file.close();
}

void scale_imgs(fs::path folder_path, fs::path output_path, double width) {
  for (auto const& img : fs::directory_iterator{folder_path}) {
    scale_img(img.path(), output_path, width);
  }
}

void to_jpg(fs::path img_path, fs::path output_path) {
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

void to_jpgs(fs::path folder_path, fs::path output_path) {
  for (auto const& img : fs::directory_iterator{folder_path}) {
    to_jpg(img.path(), output_path);
  }
}

void to_webp(fs::path img_path, fs::path output_path) {
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

void to_webps(fs::path folder_path, fs::path output_path) {
  for (auto const& img : fs::directory_iterator{folder_path}) {
    to_webp(img.path(), output_path);
  }
}

void unzip(const char *zip_path, fs::path output_path) {
  zip *zip;
  int err = 0;
  if ((zip = zip_open(zip_path, 0, &err)) == NULL) { // TODO: proper error checking
    return;
  }

  int image_count = zip_get_num_entries(zip, 0);
  struct zip_stat st;
  zip_stat_init(&st);

  for (int i = 0; i < image_count; i++) {
    zip_stat_index(zip, i, 0, &st);
    char *contents = new char[st.size];
    zip_file *f = zip_fopen_index(zip, i, 0);
    zip_fread(f, contents, st.size);
    std::ofstream file(output_path / st.name);
    file.write(contents, st.size);
    file.close();
  }
  zip_close(zip);
}

void rezip(fs::path input_path, fs::path output_path, fs::path cbz_name) {
  fs::path output_zip = output_path / cbz_name.filename();
  zip *zip;
  int err = 0;
  if ((zip = zip_open(output_zip.string().c_str(), ZIP_CREATE | ZIP_TRUNCATE, &err)) == NULL) {
    return;
  }
  for (auto const& img : fs::directory_iterator{input_path}) {
    zip_source_t *source = zip_source_file(zip, img.path().string().c_str(), 0, 0);
    zip_file_add(zip, img.path().filename().string().c_str(), source, ZIP_FL_ENC_GUESS);
  }
  zip_close(zip);
}

int main(int argc, char* argv[]) {
  fs::path executable_path = fs::canonical(argv[0]);
  fs::path project_root = executable_path.parent_path().parent_path();
  fs::path output_path = project_root / "output";
  fs::path tmp_path = project_root / "tmp";

  fs::create_directory(tmp_path / "unzipped");
  fs::path unzipped_path = tmp_path / "unzipped";
  fs::create_directory(tmp_path / "scaled");
  fs::path scaled_path = tmp_path / "scaled";
  fs::create_directory(tmp_path / "converted");
  fs::path converted_path = tmp_path / "converted";

  const char *cbz_input = argv[1];
  fs::path cbz_name = cbz_input;
  cbz_name.filename().replace_extension(".cbz");

  CBZUnzipper unzipper;
  ImageScaler scaler;
  ImageConverter converter;

  unzipper.unzip(cbz_input, unzipped_path);
  scaler.scale_imgs(unzipped_path, scaled_path, 1264);
  converter.to_webps(scaled_path, converted_path); 

  rezip(converted_path, output_path, cbz_name);
}

