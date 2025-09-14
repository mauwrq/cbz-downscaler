#include <iostream>
#include <string.h>
#include <zip.h>
#include <fstream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <boost/program_options.hpp>
#include <vector>
#include <argument_parser.hpp>
#include "cbz_tools.hpp"
#include "image_scaler.hpp"
#include "image_converter.hpp"
#include "path_tools.hpp"

namespace fs = std::filesystem;
namespace po = boost::program_options;

int main(int argc, char* argv[]) {
  // po::options_description desc("Allowed options");
  // desc.add_options()
  //   ("cbz", po::value<std::vector<std::string>>(), "cbz file(s) to downscale");
  
  // po::positional_options_description p;
  // p.add("cbz", -1);
  
  // po::variables_map vm;
  // po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(),vm);
  // po::notify(vm);

  // if (vm.count("cbz")) {
  //   auto cbz_files = vm["cbz"].as<std::vector<std::string>>();
  //   if (!cbz_files.empty()) {
  //       std::cout << "First file: " << cbz_files[1] << std::endl;
  //   }
  // }
  // std::cout << "darn" << std::endl;

  // const char *cbz_input = argv[1];
  // fs::path cbz_name = cbz_input;
  // cbz_name.filename().replace_extension(".cbz");

  ArgumentParser arg_parser;
  PathTools path_tools;
  CBZTools cbz_tools;
  ImageScaler scaler;
  ImageConverter converter;
  
  ArgumentParser::args args;
  PathTools::project_paths project_paths;
  PathTools::tmp_paths tmp_paths;

  args = arg_parser.parse_args(argc, argv);
  std::string cbz_input = args.input[0];

  project_paths = path_tools.init_project_paths(fs::canonical(argv[0]));
  tmp_paths = path_tools.init_tmp_paths(cbz_input, project_paths);
  cbz_tools.unzip(cbz_input, tmp_paths.unzipped);
  scaler.scale_imgs(tmp_paths.unzipped, tmp_paths.scaled, 1264);
  converter.to_webps(tmp_paths.scaled, tmp_paths.converted); 
  cbz_tools.rezip(tmp_paths.converted, project_paths.output, cbz_input);
}

