#pragma once
#include <filesystem>
#include <string>

class CBZTools {
  public:
    void unzip(std::string zip_path_str, std::filesystem::path output_path);
    void rezip(std::filesystem::path input_path, std::filesystem::path output_path, std::string cbz_name);
};
