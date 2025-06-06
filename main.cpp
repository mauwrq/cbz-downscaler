#include <iostream>
#include <string.h>
#include <zip.h>

int main(int argc, char* argv[]) {
  zip *cbz;
  const char *cbz_input;
  cbz_input = argv[1];
  int err = 0;
  if ((cbz = zip_open(cbz_input, 0, &err)) == NULL) { // TODO: proper error checking
    return 0;
  }
  zip_close(cbz);
}

