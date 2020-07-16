#ifndef __WALK_H__
#define __WALK_H__

#include <filesystem>
#include <functional>
#include <vector>

namespace walk {
  namespace fs = std::filesystem;

  using walkfn = std::function<void(fs::path, fs::file_status)>;

  void walk(fs::path base, walkfn fn) {
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

  void walk_files(fs::path base, walkfn fn) {
    auto func = [fn](fs::path p, fs::file_status s) {
      if (fs::is_regular_file(s)) {
        fn(p, s);
      }
    };
    walk(base, func);
  }

  void walk_dirs(fs::path base, walkfn fn) {
    auto func = [fn](fs::path p, fs::file_status s) {
      if (fs::is_directory(s)) {
        fn(p, s);
      }
    };
    walk(base, func);
  }

  std::vector<fs::path> glob(fs::path, std::string pattern) {
    std::vector<fs::path> vs;
    return vs;
  }
}

#endif
