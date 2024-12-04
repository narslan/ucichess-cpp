#include "../../src/ucichess/uci/engine.hpp"
#include "nonstd/expected.hpp"
#include <fmt/core.h>
#include <string>
using namespace nonstd;
using namespace std::literals;

auto spin_engine(std::string path) -> expected<std::string, std::string> {
  ucichess::ChessEngine e{path};

  std::string bm = e.bestMove();

  if(bm != "a3") {
    e.quit();
    return bm;
  }
  else {
    e.quit();
    return make_unexpected("'"s + bm + "' isn't a number");
  }
}

int main() {

  auto es = spin_engine("stockfish");
  if(es)
    fmt::print("{}\n", es->data());
  else
    fmt::print("{}\n", es.error());
  return 0;
}