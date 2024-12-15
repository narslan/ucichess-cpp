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
    m_counter.increment_if_not_zero();

    std::string event, site, date, eco, player1, player2, result;
    auto moves_string =
        std::accumulate(alist.begin(),
                        alist.end(),
                        std::string(),
                        [](const std::string& a, const std::string& b) -> std::string {
                          return a + (a.length() > 0 ? "," : "") + b;
                        });

    for(auto el : headers) {
      if(el.first == "Event") {
        event = el.second;
      }
      if(el.first == "Site") {
        site = el.second;
      }
      if(el.first == "Date") {
        date = el.second;
      }
      if(el.first == "Eco") {
        eco = el.second;
      }
      if(el.first == "White") {
        player1 = el.second;
      }
      if(el.first == "Black") {
        player2 = el.second;
      }
      if(el.first == "Result") {
        player2 = el.second;
      }
    }
    auto query = fmt::format("insert into pgn values ({},{},{},{},{},{},{},{},{} ) ",
                             event,
                             site,
                             date,
                             eco,
                             player1,
                             player2,
                             result,
                             moves_string);

    fmt::print("number of pgn  files: {} \n", m_counter.read() - 1);
  }

} // namespace pgn2sqlite