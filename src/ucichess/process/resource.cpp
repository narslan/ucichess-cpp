#include "resource.hpp"

#include <bits/types/struct_rusage.h>

namespace ucichess {

  long Resource::memusage() {
    struct rusage usage;
    int ret;
    ret = getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss; // in KB
  } // namespace ucichess
} // namespace ucichess
