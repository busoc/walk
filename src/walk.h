#ifndef __WALK_H__
#define __WALK_H__

#include <filesystem>
#include <functional>
#include <vector>

namespace walk {
  namespace fs = std::filesystem;

  using walkfn = std::function<void(fs::path, fs::file_status)>;

  void walk(fs::path base, walkfn fn);

  void walk_files(fs::path base, walkfn fn);

  void walk_dirs(fs::path base, walkfn fn);

  // std::vector<fs::path> glob(fs::path, std::string pattern) {
  //   std::vector<fs::path> vs;
  //   return vs;
  // }
}

#endif
