#include "parse.hpp"

namespace pgn2sqlite {

  void Parser::startPgn() {
    board.setFen(constants::STARTPOS);
    db->migrate();
  }

  void Parser::header(std::string_view key, std::string_view value) {

    //std::cout << key << " : " << value << "\n";
  }

  void Parser::startMoves() {

    std::cout << "\n-----Moves ----\n";
  }

  void Parser::move(std::string_view move, std::string_view comment) {

    auto m = uci::parseSan(board, move);
    board.makeMove(m);

    //fmt::print("{}\n", board.inCheck());
  }

  void Parser::endPgn() {
    std::string b = board.getFen();
  }
} // namespace pgn2sqlite