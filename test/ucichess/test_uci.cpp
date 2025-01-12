#include "../../src/ucichess/uci/engine.hpp"
#include <fmt/core.h>

const std::string engine_a = "patricia";
const std::string engine_b = "zahak";
const std::string engine_c = "stockfish";

int main() {

  ucichess::ChessEngine ce{engine_a};
  ce.newGame();
  ce.setPosition(R"(2r4k/1p1b1p2/4pN1p/p2pPP1P/P7/1P2B1R1/6P1/6K1 b)", "");
  auto x = ce.bestMove(20);
  // auto m = std::get<2>(x);
  fmt::print("{}", x);
}
