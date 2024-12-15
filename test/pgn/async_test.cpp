#include "../../src/ucichess/pgn/async_simple.hpp"
#include "async_simple/coro/SyncAwait.h"
#include <fmt/core.h>

int main() {
  int Num = syncAwait(pgn2sqlite::CountFileCharNum("demo_example/Input/file.txt", 'x'));

  fmt::print("{}\n", Num);
  return 0;
}