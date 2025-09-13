#include <iostream>
#include <string.h>
#include <zip.h>
#include <fstream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include "cbz_tools.hpp"
#include "image_scaler.hpp"
#include "image_converter.hpp"
#include "path_tools.hpp"

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  const char *cbz_input = argv[1];
  fs::path cbz_name = cbz_input;
  cbz_name.filename().replace_extension(".cbz");

  PathTools path_tools;
  CBZTools cbz_tools;
  ImageScaler scaler;
  ImageConverter converter;
  PathTools::project_paths project_paths;
  PathTools::tmp_paths tmp_paths;

  project_paths = path_tools.init_project_paths(fs::canonical(argv[0]));
  tmp_paths = path_tools.init_tmp_paths(cbz_name, project_paths);
  cbz_tools.unzip(cbz_input, tmp_paths.unzipped);
  scaler.scale_imgs(tmp_paths.unzipped, tmp_paths.scaled, 1264);
  converter.to_webps(tmp_paths.scaled, tmp_paths.converted); 
  cbz_tools.rezip(tmp_paths.converted, project_paths.output, cbz_name);
}

