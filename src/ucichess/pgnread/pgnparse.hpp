#include <fmt/core.h>
#include <iostream>
#include <string_view>

#include "../chess/chess.hpp"

using namespace chess;

class MyVisitor : public pgn::Visitor {
  public:
  virtual ~MyVisitor() { }

  void startPgn() {
    board.setFen(constants::STARTPOS);
  }

  void header(std::string_view key, std::string_view value) {

    //std::cout << key << " : " << value << "\n";
  }

  void startMoves() {

    std::cout << "\n-----Moves ----\n";
  }

  void move(std::string_view move, std::string_view comment) {

    auto m = uci::parseSan(board, move);
    board.makeMove(m);

    //fmt::print("{}\n", board.inCheck());
  }

  void endPgn() {
    std::string b = board.getFen();
  }

  private:
  Board board;
};
