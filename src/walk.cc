#include "walk.h"

namespace fs = std::filesystem;

void walk::walk(fs::path base, walkfn fn) {
  fs::file_status s = fs::status(base);
  if (!fs::is_directory(s)) {
    fn(base, s);
    return ;
  }
  fn(base, s);
  auto it = fs::recursive_directory_iterator(base, fs::directory_options::skip_permission_denied);
  for (auto& e: it) {
    fn(e.path(), e.status());
  }
}

void walk::walk_files(fs::path base, walkfn fn) {
  auto func = [fn](fs::path p, fs::file_status s) {
    if (fs::is_regular_file(s)) {
      fn(p, s);
    }
  };
  walk(base, func);
}

void walk::walk_dirs(fs::path base, walkfn fn) {
  auto func = [fn](fs::path p, fs::file_status s) {
    if (fs::is_directory(s)) {
      fn(p, s);
    }
  };
  walk(base, func);
}
