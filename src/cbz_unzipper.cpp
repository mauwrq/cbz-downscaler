#include "cbz_unzipper.hpp"
#include <zip.h>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void CBZUnzipper::unzip(const char *zip_path, fs::path output_path) {
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
