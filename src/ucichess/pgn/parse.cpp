#include "parse.hpp"
#include <utility>

namespace pgn2sqlite {

  Parser::Parser()
      : db{std::make_unique<pgn2sqlite::pgndb>("abdo.db")} {
    db->migrate();
  };

  void Parser::startPgn() {
    board.setFen(constants::STARTPOS);

    fmt::print("Start pgn:\n");
  }

  void Parser::header(std::string_view key, std::string_view value) {

    fmt::print("{}: {}\n", key, value);
    headers.emplace_back(std::make_pair(key, value));
  }

  void Parser::startMoves() {

    fmt::print("Start Moves:\n");
    headers.clear();
    moves.clear();
  }

  void Parser::move(std::string_view move, std::string_view comment) {

    auto m = uci::parseSan(board, move);
    board.makeMove(m);
    moves.push_back(move);

    fmt::print(" {} ", move);
  }

  void Parser::endPgn() {
    std::string b = board.getFen();

    fmt::print("End pgn:\n");
  }
} // namespace pgn2sqlite