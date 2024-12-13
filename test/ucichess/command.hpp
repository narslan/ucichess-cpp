#pragma once

#include "ucichess/uci/engine.hpp"
#include <string>
#include <vector>
namespace ucichess {

  using StrArgs = std::vector<std::string>;
  struct command {
    std::string name;
    void (*func)(ChessEngine& ce, std::string param);
  };

  //   bool quit_flag = false;

  void UCIQuit(ChessEngine& ce, std::string);
  void UCIGo(ChessEngine& ce, std::string depth);
  void UCIIsReady(ChessEngine& ce, std::string);
  void UCIPosition(ChessEngine& ce, std::string param);
  void UCISetOption(ChessEngine& ce, std::string param);
  void UCIInfo(ChessEngine& ce, std::string param);
  void UCIBest(ChessEngine& ce, std::string depth);

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