#include <iostream>
#include <string.h>
#include <zip.h>
#include <fstream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include "cbz_tools.hpp"
#include "image_scaler.hpp"
#include "image_converter.hpp"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  fs::path executable_path = fs::canonical(argv[0]);
  fs::path project_root = executable_path.parent_path().parent_path();
  fs::create_directory("output");
  fs::path output_path = project_root / "output";
  fs::create_directory("tmp");
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

  CBZTools cbz_tools;
  ImageScaler scaler;
  ImageConverter converter;

  cbz_tools.unzip(cbz_input, unzipped_path);
  scaler.scale_imgs(unzipped_path, scaled_path, 1264);
  converter.to_webps(scaled_path, converted_path); 
  cbz_tools.rezip(converted_path, output_path, cbz_name);
}

