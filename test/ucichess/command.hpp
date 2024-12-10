#pragma once

#include "ucichess/uci/engine.hpp"
#include <string>
#include <vector>
namespace ucichess {

  using StrArgs = std::vector<std::string>;
  struct command {
    std::string name;
    void (*func)(ChessEngine& ce);
  };

  //   bool quit_flag = false;

  void UCIQuit(ChessEngine& ce);
  void UCIGo(ChessEngine& ce);
  void UCIIsReady(ChessEngine& ce);
  void UCIPosition(ChessEngine& ce);
  void UCISetOption(ChessEngine& ce);
  void UCIInfo(ChessEngine& ce);
  void UCIBest(ChessEngine& ce);

  static std::vector<command> uci_commands{
      // UCI Commands
      {"go", UCIGo},
      {"quit", UCIQuit},
      {"isready", UCIIsReady},
      {"position", UCIPosition},
      {"setoption", UCISetOption},
      {"info", UCIInfo},
      {"best", UCIBest},
  };
} // namespace ucichess