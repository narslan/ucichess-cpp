#pragma once

#include <string_view>
namespace ucichess {

  struct Evaluation {

    int depth;
    int score;
    int hashfull;
    int time;
    int nodes;
    std::string_view line;
  };

} // namespace ucichess