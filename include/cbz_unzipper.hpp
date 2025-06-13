#pragma once
#include <filesystem>

class CBZUnzipper {
  public:
    void unzip(const char *zip_path, std::filesystem::path output_path);
};
