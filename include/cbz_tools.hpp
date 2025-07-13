#pragma once
#include <filesystem>

class CBZTools {
  public:
    void unzip(const char *zip_path, std::filesystem::path output_path);
    void rezip(std::filesystem::path input_path, std::filesystem::path output_path, std::filesystem::path cbz_name);
};
