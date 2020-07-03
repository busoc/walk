#include <iostream>
#include <filesystem>
#include "walk.h"
#include "flag.h"

namespace fs = std::filesystem;

int main(int argc, char** argv) {
  bool skip = false;
  flag::Set parser;
  parser.bool_var(&skip, "s", "skip", "skip directories");
  parser.parse(argc, argv);

  auto fn = [skip](fs::path p, fs::file_status s) {
    if (skip && fs::is_directory(s)) {
      return ;
    }
    std::cout << "current: " << p << std::endl;
  };
  walk::walk(parser.arg(0), fn);
}
