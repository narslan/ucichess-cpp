#pragma once

#include "process.hpp"
#include <string>
#include <vector>
namespace ucichess {

  using StrArgs = std::vector<std::string>;
  struct command {
    std::string name;
    void (*func)(ChessEngine& ce, const StrArgs args);
  };

  //   bool quit_flag = false;

  void UCIQuit(ChessEngine& ce, const StrArgs args);
  void UCIGo(ChessEngine& ce, const StrArgs args);
  void UCIIsReady(ChessEngine& ce, const StrArgs args);
  void UCIPosition(ChessEngine& ce, const StrArgs args);
  void UCISetOption(ChessEngine& ce, const StrArgs args);
  void UCIStop(ChessEngine& ce, const StrArgs args);
  void UCIBest(ChessEngine& ce, const StrArgs args);

  const std::vector<command> uci_commands{
      // UCI Commands
      {"go", UCIGo},
      {"quit", UCIQuit},
      {"isready", UCIIsReady},
      {"position", UCIPosition},
      {"setoption", UCISetOption},
      {"stop", UCIStop},
      {"best", UCIBest},
  };

  const std::string kEngineIsReady = "isready";
  const std::string kEngineNamePrefix = "id name ";
  const std::string kEngineAuthorPrefix = "id author ";
  const std::string kOk = "uciok";

} // namespace ucichess