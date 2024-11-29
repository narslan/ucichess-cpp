#include "resource.hpp"

namespace ux {

  long Resource::memusage() {
    struct rusage usage;
    int ret;
    ret = getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss; // in KB
  } // namespace ucichess
} // namespace ux
