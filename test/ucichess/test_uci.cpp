#include "../../src/ucichess/uci/engine.hpp"
#include <fmt/core.h>

const std::string engine_a = "patricia";
const std::string engine_b = "zahak";
const std::string engine_c = "stockfish";

int main() {

  ucichess::ChessEngine ce{engine_c};
  ce.newGame();
  //ce.setPosition(R"(8/7p/7P/8/2k5/2P2p2/4r3/3qBK2 b - - 1 81)", "");
  ce.setPosition(R"(rnb4r/ppp1k1pp/3bp3/1N3p2/1P2n3/P3BN2/2P1PPPP/R3KB1R b KQ - 4 11)");
  auto x = ce.bestMove(20);

  fmt::print("{}\n", x);

  
  ce.multipv(4);
  ce.threads(4);
  ce.hash(256);

  ce.newGame();
  ce.setPosition(R"(rnb4r/ppp1k1pp/3bp3/1N3p2/1P2n3/P3BN2/2P1PPPP/R3KB1R b KQ - 4 11)");

  auto analyze_result = ce.analyze(20);

  for (const auto& e: analyze_result) {
    
    fmt::print("e.time: {} e.score: {} bm: {}\n", e.time, e.score, e.bestmove);
  }
  
}
