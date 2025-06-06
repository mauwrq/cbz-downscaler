#include <iostream>
#include <string.h>
#include <zip.h>

// for now just take a file as input can do rest later
int main(int argc, char* argv[]) {
  std::string cbz_input;
  if (argc >= 2) {
    cbz_input = argv[1];
    std::cout << cbz_input << std::endl;
  }
}

