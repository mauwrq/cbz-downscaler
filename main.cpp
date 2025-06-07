#include <iostream>
#include <string.h>
#include <zip.h>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  fs::path executable_path = fs::canonical(argv[0]);
  fs::path project_root = executable_path.parent_path().parent_path();

  zip *cbz;
  const char *cbz_input;
  cbz_input = argv[1];
  int err = 0;
  if ((cbz = zip_open(cbz_input, 0, &err)) == NULL) { // TODO: proper error checking
    return 0;
  }
  
  // TODO: put this in its own file
  struct zip_stat st;
  zip_stat_init(&st);
  zip_stat_index(cbz, 0, 0, &st);
  char *contents = new char[st.size];
  zip_file *f = zip_fopen_index(cbz, 0, 0);
  zip_fread(f, contents, st.size);

  fs::create_directory(project_root / "output");
  fs::path output_path = project_root / "output";
  std::ofstream file(output_path / "cover.jpg");
  file.write(contents, st.size);
  file.close();
  zip_close(cbz);
}

