#include "command.hpp"

namespace ucichess {

  void UCIQuit(ChessEngine& ce) {

    ce.quit();
  };

  void UCIGo(ChessEngine& ce) {
    ce.go(10);
    ce.obtainEvaluations();
  };
  void UCIBest(ChessEngine& ce) {
    auto v = ce.bestMove();
  };

  void UCIIsReady(ChessEngine& ce) {
    ce.isready();
  };
  void UCIPosition(ChessEngine& ce){};
  void UCISetOption(ChessEngine& ce) {
    ce.setOption("MultiPV", 3);
  };
  void UCIInfo(ChessEngine& ce){
      //ce.getOptions();
  };

} // namespace ucichess