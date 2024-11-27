#pragma once
#include <memory>
#include <sys/resource.h>

namespace ucichess {

  using rp = std::unique_ptr<rusage>;
  class Resource {
    public:
    static long memusage();
  };

} // namespace ucichess
