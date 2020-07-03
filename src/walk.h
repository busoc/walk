#include <filesystem>
#include <functional>

namespace walk {

  namespace fs = std::filesystem;

  void walk(fs::path base, std::function<void(fs::path, fs::file_status)> fn) {
    fs::file_status s = fs::status(base);
    if (!fs::is_directory(s)) {
      fn(base, s);
      return ;
    }
    fn(base, s);
    auto it = fs::recursive_directory_iterator(base, fs::directory_options::skip_permission_denied);
    for (auto& e: it) {
      if (e.is_regular_file()) {
        fn(e.path(), e.status());
        continue;
      }
      walk(e.path(), fn);
    }
  }
}
