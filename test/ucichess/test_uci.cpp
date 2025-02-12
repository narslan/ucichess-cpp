#include "../../src/ucichess/uci/engine.hpp"
#include <fmt/core.h>

const std::string engine_a = "patricia";
const std::string engine_b = "zahak";
const std::string engine_c = "stockfish";

int main() {

  ucichess::ChessEngine ce{engine_c};
  ce.newGame();
  ce.setPosition(R"(8/7p/7P/8/2k5/2P2p2/4r3/3qBK2 b - - 1 81)", "");
  auto x = ce.bestMove(20);
  // auto m = std::get<2>(x);
  fmt::print("{}\n", x);

  auto a = ce.analyze(20);
  // auto m = std::get<2>(x);
  const std::string& score = std::get<0>(a);
  const std::string& selDepth = std::get<1>(a);
  const std::string& bestMove = std::get<2>(a);
 
  fmt::print("depth: {} score: {}\n", selDepth, score, bestMove);

  ce.newGame();
  ce.setPosition(R"(rnb4r/ppp1k1pp/3bp3/1N3p2/1P2n3/P3BN2/2P1PPPP/R3KB1R b KQ - 4 11)", "");

  auto analyze_result = ce.analyze_detail(20);

  for (const auto& e: analyze_result) {
   
    fmt::print("e.time: {} e.score: {} bm: {}\n", e.time, e.score, e.bestmove);
  }
  
  
  
}
