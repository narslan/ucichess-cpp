#include "command.hpp"

namespace ucichess {

  void UCIQuit(ChessEngine& ce, const StrArgs args) {

    ce.quit();
  };

  void UCIGo(ChessEngine& ce, const StrArgs args) {
    ce.go();
    ce.obtainEvaluations();
  };
  void UCIBest(ChessEngine& ce, const StrArgs args) {
    auto v = ce.bestMove();
  };

  void UCIIsReady(ChessEngine& ce, const StrArgs args) {
    ce.isready();
  };
  void UCIPosition(ChessEngine& ce, const StrArgs args){};
  void UCISetOption(ChessEngine& ce, const StrArgs args){};
  void UCIStop(ChessEngine& ce, const StrArgs args){};

} // namespace ucichess