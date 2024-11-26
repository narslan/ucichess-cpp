#include "resource.hpp"

#include <bits/types/struct_rusage.h>

#include <fmt/core.h>

namespace chessbird {

  long Resource::memusage() {
    struct rusage usage;
    int ret;
    ret = getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss; // in KB
  } // namespace chessbird
} // namespace chessbird
