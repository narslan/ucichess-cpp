#include <fmt/core.h>

#include "../../src/ucichess/pgn/async_simple.hpp"

int main() {
  int Num = syncAwait(pgn2sqlite::CountFileCharNum("demo_example/Input/file.txt", 'x'));

  fmt::print("{}\n", Num);
  return 0;
}