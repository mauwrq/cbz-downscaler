#include <path_tools.hpp>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

PathTools::project_paths PathTools::init_project_paths(fs::path executable_path) {
  PathTools::project_paths project_paths;
  fs::path project_root = executable_path.parent_path().parent_path();
  fs::create_directory("output");
  project_paths.output = project_root / "output";
  fs::create_directory("tmp");
  project_paths.tmp = project_root / "tmp";
  return project_paths;
};
  
PathTools::tmp_paths PathTools::init_tmp_paths(std::string cbz_name_str, PathTools::project_paths project_paths) {
  fs::path cbz_name = cbz_name_str;
  PathTools::tmp_paths tmp_paths;
  fs::create_directory(project_paths.tmp / cbz_name.filename());
  fs::path tmp_cbz_path = project_paths.tmp / cbz_name.filename();
  fs::create_directory(tmp_cbz_path / "unzipped");
  tmp_paths.unzipped = tmp_cbz_path / "unzipped";
  fs::create_directory(tmp_cbz_path / "scaled");
  tmp_paths.scaled = tmp_cbz_path / "scaled";
  fs::create_directory(tmp_cbz_path / "converted");
  tmp_paths.converted = tmp_cbz_path / "converted";
  return tmp_paths;
};