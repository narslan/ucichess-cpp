#include "command.hpp"

namespace uci {

  void UCIQuit(ChessEngine& ce, const StrArgs args) {

    ce.quit();
  };

  void UCIGo(ChessEngine& ce, const StrArgs args) {
    ce.go();
    ce.obtainEvaluations();
  };
  void UCIBest(ChessEngine& ce, const StrArgs args) {
    auto v = ce.bestMove();
    fmt::print("best move: {}\n", v);
  };

  void UCIIsReady(ChessEngine& ce, const StrArgs args) {
    ce.isready();
  };
  void UCIPosition(ChessEngine& ce, const StrArgs args){};
  void UCISetOption(ChessEngine& ce, const StrArgs args){};
  void UCIStop(ChessEngine& ce, const StrArgs args){};
} // namespace uci