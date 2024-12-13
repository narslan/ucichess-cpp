#include "command.hpp"
#include <string>

namespace ucichess {

  void UCIQuit(ChessEngine& ce, std::string param) {

    ce.quit();
  };

  void UCIGo(ChessEngine& ce, std::string depth) {

    ce.go(std::stoi(depth));
    ce.obtainEvaluations();
  };
  void UCIBest(ChessEngine& ce, std::string param) {
    auto v = ce.bestMove();
    fmt::print("bestmove: {}\n", v);
  };

  void UCIIsReady(ChessEngine& ce, std::string param) {
    ce.isready();
  };
  void UCIPosition(ChessEngine& ce, std::string param){};
  void UCISetOption(ChessEngine& ce, std::string param) {
    ce.setOption("MultiPV", 3);
  };
  void UCIInfo(ChessEngine& ce, std::string param){
      //ce.getOptions();
  };

} // namespace ucichess