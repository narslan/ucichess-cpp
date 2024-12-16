#include "parse.hpp"
#include <cstdint>
#include <fmt/format.h>
#include <memory>
#include <string>
#include <string_view>
#include <utility>

namespace pgn2sqlite {

  /*! note: delimiter cannot contain NUL characters
 */

  Parser::Parser()
      : db{std::make_unique<pgn2sqlite::pgndb>("abdo.db")} {
    db->migrate();
  };

  void Parser::startPgn() {
    board.setFen(constants::STARTPOS);
    moves_.clear();
    headers_.clear();

    game_count_.increment_if_not_zero();
    fmt::print("Start pgn: counter {}\n", game_count_.read());
  }

  void Parser::header(std::string_view key, std::string_view value) {

    headers_.push_back(std::make_pair(std::string(key), std::string(value)));

    if(key == "Result" && value == "*") {
      this->skipPgn(true);
    }
  }

  void Parser::startMoves() { }

  void Parser::move(std::string_view move, std::string_view comment) {

    uint64_t c = game_count_.read();

    moves_.push_back(std::string(move));

    auto m = uci::parseSan(board, move);

    board.makeMove(m);
  }

  bool IsEvent(std::pair<std::string, std::string> i) {
    return i.first == "Event";
  };

  bool IsSite(std::pair<std::string, std::string> i) {
    return i.first == "Site";
  };

  bool IsDate(std::pair<std::string, std::string> i) {
    return (i.first == "Date" || i.first == "UTCDate");
  };

  bool IsEco(std::pair<std::string, std::string> i) {
    return i.first == "ECO";
  };

  bool IsWhite(std::pair<std::string, std::string> i) {
    return i.first == "White";
  };

  bool IsBlack(std::pair<std::string, std::string> i) {
    return i.first == "Black";
  };

  bool IsResult(std::pair<std::string, std::string> i) {
    return i.first == "Result";
  };
  void Parser::endPgn() {

    std::string mvs;
    for(auto el : moves_) {
      mvs = mvs + " " + el;
    }

    //std::string b = board.getFen();

    std::string event, site, date, eco, player1, player2, result;

    auto it = std::find_if(headers_.begin(), headers_.end(), IsEvent);
    event = it->second;

    it = std::find_if(headers_.begin(), headers_.end(), IsSite);
    site = it->second;

    it = std::find_if(headers_.begin(), headers_.end(), IsDate);
    date = it->second;

    it = std::find_if(headers_.begin(), headers_.end(), IsEco);
    eco = it->second;

    it = std::find_if(headers_.begin(), headers_.end(), IsWhite);
    player1 = it->second;

    it = std::find_if(headers_.begin(), headers_.end(), IsBlack);
    player2 = it->second;

    it = std::find_if(headers_.begin(), headers_.end(), IsResult);
    result = it->second;

    try {
      // Begin transaction
      SQLite::Transaction transaction(db->db);
      SQLite::Statement query{db->db, "insert into pgn values (NULL,?,?,?,?,?,?,?,?)"};

      query.bind(1, event);
      query.bind(2, site);
      query.bind(3, date);
      query.bind(4, eco);
      query.bind(5, player1);
      query.bind(6, player2);
      query.bind(7, result);
      query.bind(8, mvs);
      query.exec();
      transaction.commit();

      // SQLite::Statement query2(db->db, "SELECT * FROM pgn");

      // while(query2.executeStep()) {
      //   fmt::print("{} {} \n", query2.getColumn(1).getInt(), query2.getColumn(2).getText());
      // }
      // headers.clear();
      // moves.clear();
    }
    catch(const std::exception& e) {
      fmt::print("SQLite Error {}\n", e.what());
    }
  }

} // namespace pgn2sqlite