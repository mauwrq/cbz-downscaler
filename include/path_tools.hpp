#pragma once
#include <filesystem>
#include <string>

class PathTools {
  public:
    struct project_paths {
      std::filesystem::path tmp;
      std::filesystem::path output;
    };
    struct tmp_paths {
      std::filesystem::path unzipped;
      std::filesystem::path scaled;
      std::filesystem::path converted;
    };
    project_paths init_project_paths(std::filesystem::path executable_path);
    tmp_paths init_tmp_paths(std::string cbz_name_str, project_paths project_paths);
};

